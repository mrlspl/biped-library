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
 * File:   Humanoid.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 8, 2016
 */

#include "Humanoid.hpp"
#include <ceres/ceres.h>
#include "glog/logging.h"
#include <cmath>

using ceres::NumericDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;
using ceres::CENTRAL;
using namespace BipedLibrary;

Humanoid::Humanoid(){}

Chain Humanoid::leftHand() const
{
    return leftHand_;
}

Chain Humanoid::rightHand() const
{
    return rightHand_;
}

Chain Humanoid::head() const
{
    return head_;
}

std::vector <vec3> Humanoid::detectedPoints() const
{
		return detectedPoints_;
}

std::vector <vec3> Humanoid::platePoints() const
{
		return platePoints_;
}

int Humanoid::cameraIndex() const
{
		return cameraIndex_;
}

std::vector <Camera> Humanoid::camera() const
{
		return camera_;
}


Humanoid& Humanoid::setLeftHand(Chain const& leftHand)
{
    leftHand_ = leftHand;
    return *this;
}

Humanoid& Humanoid::setRightHand(Chain const& rightHand)
{
    rightHand_ = rightHand;
    return *this;
}

Humanoid& Humanoid::setHead(Chain const& head)
{
    head_ = head;
    return *this;
}

Humanoid& Humanoid::setCamera(Camera const& camera)
{
		camera_.push_back(camera);
		return *this;
}

Humanoid& Humanoid::setCameraIndex(int const& cameraIndex)
{
		cameraIndex_ = cameraIndex;
		return *this;
}

Humanoid& Humanoid::setDetectedPoints(std::vector <vec3> detectedPoints)
{
		detectedPoints_ = detectedPoints;
		return *this;
}

Humanoid& Humanoid::setPlatePoints(std::vector <vec3> platePoints)
{
		platePoints_ = platePoints;
		return *this;
}

Chain& Humanoid::mutableLeftHand()
{
    return leftHand_;
}

Chain& Humanoid::mutableRightHand()
{
    return rightHand_;
}

Chain& Humanoid::mutableHead()
{
    return head_;
}

std::vector <Camera>& Humanoid::mutableCamera()
{
		return camera_;
}

std::vector <vec3>& Humanoid::mutableDetectedPoints()
{
		return detectedPoints_;
}

std::vector <vec3>& Humanoid::mutablePlatePoints()
{
		return platePoints_;
}


//static bool googleInitialized = false;

void Humanoid::calibrate()
{
//	if (!googleInitialized)
//	{
//		google::InitGoogleLogging("");
//		googleInitialized = true;
//	}
//
//	class f1 {
//	private:
//		Humanoid& humanoid_;
//	public:
//			f1(Humanoid& humanoid) : humanoid_(humanoid) { }
//		bool operator()(const double* const x1, double* residual) const {
//			residual[0] = x1[0] - 1;
//			residual[1] = x1[1] - 15;
////			humanoid_.mutableHead().at(0).mutableTheta() += x[0];
////			humanoid_.calculateErrors();
//			return true;
//		}
//	};
//
////	struct f2 {
////		bool operator()(const double* const x2, double* residual) const {
////			residual[0] = x2[0] - 3;
////			return true;
////		}
////	};
////
////	struct f3 {
////		bool operator()(const double* const x3, double* residual) const {
////			residual[0] = x3[0] + 3;
////			return true;
////		}
////	};
//	Problem problem;
//	double x1[2] = {0, 0}; double x2 = 0; double x3 = 0;
//	problem.AddResidualBlock(
//			new NumericDiffCostFunction<f1, CENTRAL, 2, 2>(new f1(*this)), NULL, x1);
////	problem.AddResidualBlock(
////			new NumericDiffCostFunction<f2, CENTRAL, 1, 1>(new f2), NULL, &x2);
////	problem.AddResidualBlock(
////			new NumericDiffCostFunction<f3, CENTRAL, 1, 1>(new f3), NULL, &x3);
//	Solver::Options options;
//	options.max_num_iterations = 100;
//	options.linear_solver_type = ceres::DENSE_QR;
//	options.minimizer_progress_to_stdout = true;
//	Solver::Summary summary;
//	Solve(options, &problem, &summary);
////	std::cout << summary.FullReport() << "\n";
}

void Humanoid::calculateErrors()
{
//		//PART 1: here posi_C_B_B and ori_C_B are calculated.
//		// section 1, from Torso to Base by right leg
//		const vec3 posi_RF_T_T = rightLeg().position_end_body_body();
//		const vec3 posi_RF_B_B = {0,-50,0};
//		const mat33 ori_RF_T = rightLeg().orientation_end_body();
//		const mat33 ori_rT_B = trans(ori_RF_T);
//		const vec3 posi_rT_B_B = - ori_rT_B * posi_RF_T_T + posi_RF_B_B;
//
//		// section 1.5, from Torso to Base by left leg
//		const vec3 posi_LF_T_T = leftLeg().position_end_body_body();
//		const vec3 posi_LF_B_B = {0,50,0};
//		const mat33 ori_LF_T = leftLeg().orientation_end_body();
//		const mat33 ori_lT_B = trans(ori_LF_T);
//		const vec3 posi_lT_B_B = - ori_lT_B * posi_LF_T_T + posi_LF_B_B;
//
//		//section 1.6
//		const vec3 posi_T_B_B = ( posi_lT_B_B + posi_rT_B_B ) / 2;
//		const mat33 ori_T_B = ( ori_rT_B + ori_lT_B ) / 2;
//
//		//section 2, from Head to Base
//		const vec3 posi_H_T_T = head().position_end_body_body();
//		const mat33 ori_H_T = head().orientation_end_body();
//		const mat33 ori_H_B = ori_T_B * ori_H_T;
//		const vec3 posi_H_B_B = ori_T_B * posi_H_T_T + posi_T_B_B;
//
//		int cameraNumber;
//		//section 3, from Camera to Base
//		vec3 posi_C_H_H = camera().at(cameraNumber).position();
//		mat33 ori_C_H = camera().at(cameraNumber).orientation();
//
//		mat33 ori_C_B = ori_H_B * ori_C_H;
//		mat33 ori_I_B = ori_C_B * AxisAngle( { 0, 1, 0 },  M_PI_2).rotationMatrix()
//																										* AxisAngle( { 0, 0, 1 }, -M_PI_2).rotationMatrix();
//		vec3 posi_C_B_B = ori_H_B * posi_C_H_H + posi_H_B_B;
//
//
//		float f_C = camera().at(cameraNumber).imageSize().at(0) / (2 *  std::tan(camera().at(cameraNumber).openAngle().toFloat() / 2));
//		//PART 2: here sample points from plate of current state get sorted
//		// in order to get their difference with ordered points from plate
//		std::vector<vec_index> unprojectedPoints;
//		for (size_t i=0; i<detectedPoints().size(); i++)
//				{
//						vec3 posi_Pi_C_C ;
//						posi_Pi_C_C.at(0) = detectedPoints().at(i).at(0) - (camera().at(cameraNumber).imageSize().at(0) / 2);
//						posi_Pi_C_C.at(1) = detectedPoints().at(i).at(1) - (camera().at(cameraNumber).imageSize().at(1) / 2);
//
//						posi_Pi_C_C.at(2) = f_C;
//						vec3 posi_Pi_C_B = ori_I_B * posi_Pi_C_C;
//
//						float a = - posi_C_B_B.at(2) / posi_Pi_C_B.at(2);
//						vec3 posi_P_C_B = a * posi_Pi_C_B;
//						vec3 posi_P_B_B = posi_C_B_B + posi_P_C_B;
//
//						vec_index newPoint;
//						newPoint.index = i;
//						newPoint.point = posi_P_B_B;
//
//						unprojectedPoints.push_back(newPoint);
//				}
//
//		std::sort (unprojectedPoints.begin(), unprojectedPoints.end(), [](const vec_index& a, const vec_index& b) {
//				return a.point[0] < b.point[0];
//		});
//		std::sort (unprojectedPoints.begin(), unprojectedPoints.begin()+2, [](const vec_index& a, const vec_index& b) {
//				return a.point[1] < b.point[1];
//		});
//		std::sort (unprojectedPoints.begin()+3, unprojectedPoints.begin()+5, [](const vec_index& a, const vec_index& b) {
//				return a.point[1] < b.point[1];
//		});
//		std::sort (unprojectedPoints.begin()+6, unprojectedPoints.end(), [](const vec_index& a, const vec_index& b) {
//				return a.point[1] < b.point[1];
//		});
//
//		//PART 3: here point errors are calculated and added to platePoints vector
//		for (size_t i=0; i<detectedPoints().size(); i++)
//				{
//						vec3 posi_Pw_B_B = platePoints().at(i);
//						vec3 posi_Pw_C_C = trans(ori_I_B) * (posi_Pw_B_B - posi_C_B_B);
//
//						float a = posi_Pw_C_C.at(2) / f_C;
//
//						//section 5
//						vec3 posi_Pi_C_C;
//						posi_Pi_C_C.at(0) = (1/a) * posi_Pw_C_C.at(0);
//						posi_Pi_C_C.at(1) = (1/a) * posi_Pw_C_C.at(1);
//						posi_Pi_C_C.at(2) = f_C;
//
//						float Width = camera().at(cameraNumber).imageSize().at(0) , Height = camera().at(cameraNumber).imageSize().at(1);
//						float xi = posi_Pi_C_C.at(0) + Width/2;
//						float yi = posi_Pi_C_C.at(1) + Height/2;
//
//						vec2 newPoint = {detectedPoints().at(unprojectedPoints.at(i).index).at(0) - xi,
//																							detectedPoints().at(unprojectedPoints.at(i).index).at(1) - yi};
////						PlatePoints.push_back(newPoint);
//				}
}
