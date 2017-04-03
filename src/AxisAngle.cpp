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
 * File:   AxisAngle.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 22, 2016
 */

#include "AxisAngle.hpp"
#include "Utility.hpp"

using namespace BipedLibrary;
using namespace BipedLibrary::Utility;

AxisAngle::AxisAngle(vec3 axis, Angle angle) :
axis_(axis),
angle_(angle)
{
}

mat33 AxisAngle::rotationMatrix() const
{
    vec3 u = normalise(axis_);
    return angle_.cos() * eye(3, 3) + angle_.sin() * crossProductMatrix(u)
           + (1 - angle_.cos()) * u * u.t();
}

vec3 AxisAngle::axis() const
{
    return axis_;
}

Angle AxisAngle::angle() const
{
    return angle_;
}

vec3 AxisAngle::asAVector() const
{
	return angle_.toFloat() * normalise(axis_);
}

AxisAngle& AxisAngle::setAxis(vec3 const& axis)
{
    axis_ = axis;
    return *this;
}

AxisAngle& AxisAngle::setAngle(Angle const& angle)
{
    angle_ = angle;
    return *this;
}

vec3& AxisAngle::mutableAxis()
{
    return axis_;
}

Angle& AxisAngle::mutableAngle()
{
    return angle_;
}
