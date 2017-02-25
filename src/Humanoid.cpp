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