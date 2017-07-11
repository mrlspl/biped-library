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
 * File:   Humanoid.hpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on March 17, 2016
 */

#pragma once

#include "Biped.hpp"

#include <vector>

namespace BipedLibrary
{

    class Humanoid : public Biped
    {
    public:
        Humanoid();
        
        Chain leftHand() const;
        Chain rightHand() const;
        Chain head() const;
        
        Humanoid& setLeftHand(Chain const& leftHand);
        Humanoid& setRightHand(Chain const& rightHand);
        Humanoid& setHead(Chain const& head);
        
        Chain& mutableLeftHand();
        Chain& mutableRightHand();
        Chain& mutableHead();
        void calibrate();
        

    private:
        Chain leftHand_;
        Chain rightHand_;
        Chain head_;
        
    };

}
