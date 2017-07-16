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
 * File:   DHFrame.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 * 
 * Created on February 29, 2016
 */

#include <stdexcept>
#include <limits>

#include "DHFrame.hpp"
#include "unit-test/DHFrameTestSuite.h"

using namespace BipedLibrary;

unsigned DHFrame::lastGenaratedId_ = 0;

DHFrame::DHFrame(Angle const alpha, Angle const theta, float const r, float const d) :
id_(++lastGenaratedId_),
theta_(theta),
deltaTheta_(0),
alpha_(alpha),
r_(r),
d_(d)
{
    if (lastGenaratedId_ == std::numeric_limits<unsigned>::max())
        throw (std::out_of_range("Too many DHFrames constructed. Overflow on id"));
}

unsigned DHFrame::id() const
{
    return id_;
}

Angle DHFrame::deltaTheta() const
{
		return deltaTheta_;
}

Angle DHFrame::theta() const
{
    return theta_ + deltaTheta();
}

Angle DHFrame::alpha() const
{
    return alpha_;
}

float DHFrame::r() const
{
    return r_;
}

float DHFrame::d() const
{
    return d_;
}

DHFrame& DHFrame::setTheta(Angle const theta)
{
    theta_ = theta;
    return *this;
}

DHFrame& DHFrame::setDeltaTheta(Angle const deltaTheta)
{
				deltaTheta_ = deltaTheta;
				return *this;
}

DHFrame& DHFrame::setAlpha(Angle const alpha)
{
    alpha_ = alpha;
    return *this;
}

DHFrame& DHFrame::setR(float const r)
{
    r_ = r;
    return *this;
}

DHFrame& DHFrame::setD(float const d)
{
    d_ = d;
    return *this;
}

bool DHFrame::operator==(DHFrame const& other)
{
    return id_ == other.id_;
}
