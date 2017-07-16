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
 * File:   DHFrame.hpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 29, 2016, 9:21 PM
 */

#pragma once

#include <vector>
#include <armadillo>

#include "Angle.hpp"

namespace BipedLibrary
{
    using namespace arma;

    class DHFrame
    {
    public:
        DHFrame(Angle const alpha = 0,
                Angle const theta = 0,
                float const r = 0,
                float const d = 0);

        unsigned id() const;
        Angle theta() const;
        Angle deltaTheta() const;
        Angle alpha() const;
        float r() const;
        float d() const;

        DHFrame& setTheta(Angle const theta);
        DHFrame& setDeltaTheta(Angle const deltaTheta);
        DHFrame& setAlpha(Angle const alpha);
        DHFrame& setR(float const r);
        DHFrame& setD(float const d);
        
        bool operator==(DHFrame const& other);

    private:
        unsigned id_;
        static unsigned lastGenaratedId_;
        Angle theta_;
        Angle deltaTheta_;
        Angle alpha_;
        float r_;
        float d_;
    };

}
