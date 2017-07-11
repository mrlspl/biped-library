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

using ceres::NumericDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;
using ceres::CENTRAL;
using namespace BipedLibrary;

Humanoid::Humanoid()
{
}

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

static bool googleInitialized = false;

void Humanoid::calibrate()
{
	if (!googleInitialized)
	{
		google::InitGoogleLogging("");
		googleInitialized = true;
	}

	struct f1 {
		bool operator()(const double* const x1, double* residual) const {
			residual[0] = x1[0] - 1;
			return true;
		}
	};

	struct f2 {
		bool operator()(const double* const x2, double* residual) const {
			residual[0] = x2[0] - 3;
			return true;
		}
	};

	struct f3 {
		bool operator()(const double* const x3, double* residual) const {
			residual[0] = x3[0] + 3;
			return true;
		}
	};
	Problem problem;
	double x1 = 0; double x2 = 0; double x3 = 0;
	problem.AddResidualBlock(
			new NumericDiffCostFunction<f1, CENTRAL, 1, 1>(new f1), NULL, &x1);
	problem.AddResidualBlock(
			new NumericDiffCostFunction<f2, CENTRAL, 1, 1>(new f2), NULL, &x2);
	problem.AddResidualBlock(
			new NumericDiffCostFunction<f3, CENTRAL, 1, 1>(new f3), NULL, &x3);
	Solver::Options options;
	options.max_num_iterations = 100;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;
	Solver::Summary summary;
	Solve(options, &problem, &summary);
//	std::cout << summary.FullReport() << "\n";
	std::cout << "Final x1 = " << x1 << ", x2 = " << x2 << ", x3 = " << x3
			<< "\n";
}







