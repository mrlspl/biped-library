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
 * File:   Camera.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 8, 2016
 */

#include "Camera.hpp"

using namespace BipedLibrary;

Camera::Camera()
{
}

vec3 Camera::position() const
{
		return position_;
}
vec3 Camera::extrinsicCalibration() const
{
		return extrinsicCalibration_;
}
mat33 Camera::orientation() const
{
		return orientation_;
}
vec2 Camera::imageSize() const
{
		return imageSize_;
}
Angle Camera::openAngle() const
{
		return openAngle_;
}

Camera& Camera::setPosition(vec3 const& position)
{
		position_ = position;
		return *this;
}

Camera& Camera::setExtrinsicCalibration(vec3 const& extrinsicCalibration)
{
		extrinsicCalibration_ = extrinsicCalibration;
		return *this;
}

Camera& Camera::setOrientation(mat33 const& orientation)
{
		orientation_ = orientation;
		return *this;
}
Camera& Camera::setImageSize(float width, float height)
{
		imageSize_.at(0) = width;
		imageSize_.at(1) = height;
		return *this;
}

Camera& Camera::setOpenAngle(Angle const& openAngle)
{
		openAngle_ = openAngle;
		return *this;
}

Camera& Camera::setOpenAngle(float openAngle)
{
		openAngle_ = Angle(openAngle);
}

vec3& Camera::mutablePosition()
{
		return position_;
}

vec3& Camera::mutableExtinsicCalibration()
{
		return extrinsicCalibration_;
}
mat33& Camera::mutableOrientation()
{
		return orientation_;
}
vec2& Camera::mutableImageSize()
{
		return imageSize_;
}
Angle& Camera::mutableOpenAngle()
{
		return openAngle_;
}
