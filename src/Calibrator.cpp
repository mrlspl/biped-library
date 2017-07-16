/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2015 MRL-SPL RoboCup Team
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */


/* 
 * File:   Calibrator.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 8, 2016
 */

#include "Calibrator.hpp"
#include <ceres/ceres.h>
#include "glog/logging.h"
#include <assert.h>
using ceres::NumericDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;
using ceres::CENTRAL;
using namespace BipedLibrary;

Calibrator::Calibrator(){}

Humanoid Calibrator::state(int stateNumber) const
{
	return states_.at(stateNumber);
}

Calibrator& Calibrator::setState(Humanoid const& state)
{
	states_.push_back(state);
	return *this;
}

Calibrator& Calibrator::setState(Humanoid const& state, int stateNumber)
{
	states_.at(stateNumber) = state;
	return *this;
}

Humanoid& Calibrator::mutableState(int stateNumber)
{
	return states_.at(stateNumber);
}

static bool googleInitialized = false;

void Calibrator::calculateErrors()
{

	errors.resize(0);
//	for (auto i=states_.end()-1; i>states_.begin(); i--)
//		states_.erase(i);
	std::cout << "states_.size= " << states_.size() << std::endl;
	for (auto& state: states_)
	{

		//PART 1: here posi_C_B_B and ori_C_B are calculated.
		// section 1, from Torso to Base by right leg
		const vec3 posi_RF_T_T = state.rightLeg().position_end_body_body();
		const vec3 posi_RF_B_B = {0,-50,0};
		const mat33 ori_RF_T = state.rightLeg().orientation_end_body();
		const mat33 ori_rT_B = trans(ori_RF_T);
		const vec3 posi_rT_B_B = - ori_rT_B * posi_RF_T_T + posi_RF_B_B;

		// section 1.5, from Torso to Base by left leg
		const vec3 posi_LF_T_T = state.leftLeg().position_end_body_body();
		const vec3 posi_LF_B_B = {0,50,0};
		const mat33 ori_LF_T = state.leftLeg().orientation_end_body();
		const mat33 ori_lT_B = trans(ori_LF_T);
		const vec3 posi_lT_B_B = - ori_lT_B * posi_LF_T_T + posi_LF_B_B;

		//section 1.6
		const vec3 posi_T_B_B = ( posi_lT_B_B + posi_rT_B_B ) / 2;
		const mat33 ori_T_B = ( ori_rT_B + ori_lT_B ) / 2;

		//section 2, from Head to Base
		const vec3 posi_H_T_T = state.head().position_end_body_body();
		const mat33 ori_H_T = state.head().orientation_end_body();
		const mat33 ori_H_B = ori_T_B * ori_H_T;
		const vec3 posi_H_B_B = ori_T_B * posi_H_T_T + posi_T_B_B;
//		assert (
//		isnan(state.rightLeg().position_end_body_body().at(0)) ||
//		isnan(state.rightLeg().position_end_body_body().at(1)) ||
//		isnan(state.rightLeg().position_end_body_body().at(2)) ||
////		isnan(state.rightLeg().orientation_end_body().at(0)) ||
//		isnan(state.leftLeg().position_end_body_body().at(0)) ||
//		isnan(state.leftLeg().position_end_body_body().at(1)) ||
//		isnan(state.leftLeg().position_end_body_body().at(2)) ||
////		state.leftLeg().orientation_end_body().print("state.leftLeg().orientation_end_body(): ");
//		isnan(state.head().position_end_body_body().at(0)) ||
//		isnan(state.head().position_end_body_body().at(1)) ||
//		isnan(state.head().position_end_body_body().at(2)));
		std::cout << "(.Y.) -- (.Y.) -- (.Y.)" << std::endl;
//		state.head().orientation_end_body().print("state.head().orientation_end_body(): ");


		int cameraNumber = state.cameraIndex();
		//section 3, from Camera to Base
		vec3 posi_C_H_H = state.camera().at(cameraNumber).position();
		mat33 ori_C_H = state.camera().at(cameraNumber).orientation();

		mat33 ori_C_B = ori_H_B * ori_C_H;
		mat33 ori_I_B = ori_C_B * AxisAngle( { 0, 1, 0 },  M_PI_2).rotationMatrix()
														* AxisAngle( { 0, 0, 1 }, -M_PI_2).rotationMatrix();
		vec3 posi_C_B_B = ori_H_B * posi_C_H_H + posi_H_B_B;



		float f_C = state.camera().at(cameraNumber).imageSize().at(0) / (2 *  std::tan(state.camera().at(cameraNumber).openAngle().toFloat() / 2));
		//PART 2: here sample points from plate of current state get sorted
		// in order to get their difference with ordered points from plate
		std::vector<vec_index> unprojectedPoints;
		for (size_t i=0; i<state.detectedPoints().size(); i++)
		{
			vec3 posi_Pi_C_C ;
			posi_Pi_C_C.at(0) = state.detectedPoints().at(i).at(0) - (state.camera().at(cameraNumber).imageSize().at(0) / 2);
			posi_Pi_C_C.at(1) = state.detectedPoints().at(i).at(1) - (state.camera().at(cameraNumber).imageSize().at(1) / 2);

			posi_Pi_C_C.at(2) = f_C;
			vec3 posi_Pi_C_B = ori_I_B * posi_Pi_C_C;

			float a = - posi_C_B_B.at(2) / posi_Pi_C_B.at(2);
			vec3 posi_P_C_B = a * posi_Pi_C_B;
			vec3 posi_P_B_B = posi_C_B_B + posi_P_C_B;

			vec_index newPoint;
			newPoint.index = i;
			newPoint.point = posi_P_B_B;

			unprojectedPoints.push_back(newPoint);
		}

		std::sort (unprojectedPoints.begin(), unprojectedPoints.end(), [](const vec_index& a, const vec_index& b) {
			return a.point[0] < b.point[0];
		});
		std::sort (unprojectedPoints.begin(), unprojectedPoints.begin()+2, [](const vec_index& a, const vec_index& b) {
			return a.point[1] < b.point[1];
		});
		std::sort (unprojectedPoints.begin()+3, unprojectedPoints.begin()+5, [](const vec_index& a, const vec_index& b) {
			return a.point[1] < b.point[1];
		});
		std::sort (unprojectedPoints.begin()+6, unprojectedPoints.end(), [](const vec_index& a, const vec_index& b) {
			return a.point[1] < b.point[1];
		});

		//PART 3: here point errors are calculated and added to platePoints vector
//		std::cout << "Detected Points Size" << state.detectedPoints().size() << std::endl;
		for (size_t i=0; i<state.detectedPoints().size(); i++)
		{

			vec3 posi_Pw_B_B = state.platePoints().at(i);
			vec3 posi_Pw_C_C = trans(ori_I_B) * (posi_Pw_B_B - posi_C_B_B);

			float a = posi_Pw_C_C.at(2) / f_C;
			//section 5
			vec3 posi_Pi_C_C;
			posi_Pi_C_C.at(0) = (1/a) * posi_Pw_C_C.at(0);
			posi_Pi_C_C.at(1) = (1/a) * posi_Pw_C_C.at(1);
			posi_Pi_C_C.at(2) = f_C;
			float Width = state.camera().at(cameraNumber).imageSize().at(0) , Height = state.camera().at(cameraNumber).imageSize().at(1);
			float xi = posi_Pi_C_C.at(0) + Width/2;
			float yi = posi_Pi_C_C.at(1) + Height/2;
			vec2 newPoint = {state.detectedPoints().at(unprojectedPoints.at(i).index).at(0) - xi,
					state.detectedPoints().at(unprojectedPoints.at(i).index).at(1) - yi};
//			std::cout << "newPoint.at(" << i << ") = " << newPoint.at(0) << " , newPoint.at(" << i << ") = " << newPoint.at(1) << std::endl;
			errors.push_back(newPoint.at(0));
			errors.push_back(newPoint.at(1));
		}
		std::cout << "---------------------------------------" << std::endl;
	}

}
void Calibrator::calibrate()
{
//	for (auto& state: states_)
//	{
//		state.calculateErrors();
//	}

	if (!googleInitialized)
	{
		google::InitGoogleLogging("");
		googleInitialized = true;
	}
	class f1 {
	private:
		Calibrator& calibrator_;
	public:
		f1(Calibrator& calibrator) : calibrator_(calibrator) { }
		bool operator()(const double* const x, double* residual) const {
			//					residual[0] = x1[0] - 1;
			//					residual[1] = x1[1] - 15;
			//					humanoid_.mutableHead().at(0).mutableTheta() += x[0];
			for (auto& state: calibrator_.states_)
			{
				const int cameraSize = state.mutableCamera().size() * 3;
				const int leftLegSize = state.mutableLeftLeg().size();
				const int rightLegSize = state.mutableRightLeg().size();
				const int headSize = state.mutableHead().size();

				for (int i=0, k=0; i<cameraSize; i=i+3, k++)
					state.mutableCamera().at(k).setExtrinsicCalibration(vec3 {x[i], x[i+1], x[i+2]});
				for (int i=cameraSize, k=0; i< cameraSize + leftLegSize; i++, k++)
					state.mutableLeftLeg().at(k).setDeltaTheta(x[i]);
				for (int i=cameraSize + leftLegSize, k=0; i< cameraSize + leftLegSize + rightLegSize; i++, k++)
					state.mutableLeftLeg().at(k).setDeltaTheta(x[i]);
				for (int i=cameraSize + leftLegSize + rightLegSize, k=0; i<cameraSize + leftLegSize + rightLegSize + headSize; i++, k++)
					state.mutableHead().at(k).setDeltaTheta(x[i]);
			}
			calibrator_.calculateErrors();
			std::cout << "Size of errors= " << calibrator_.errors.size() << std::endl;
			for(int i=0; i<calibrator_.errors.size(); i++)
			{
				residual[i] = calibrator_.errors.at(i);
//				std::cout << "residule[" << i << "]= " << residual[i] << "			";
			}
			std::cout << std::endl;

			return true;
		}
	};

	Problem problem;
	double x[20];
	for (int i=0; i<20; i++)
		x[i] = 0;
	problem.AddResidualBlock(
			new NumericDiffCostFunction<f1, CENTRAL, 126, 20>(new f1(*this)), NULL, x);
	Solver::Options options;
	options.max_num_iterations = 1000;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;
	Solver::Summary summary;
	Solve(options, &problem, &summary);
	std::cout << summary.FullReport() << "\n";
}
