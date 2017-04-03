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
 * File:   Chain.hpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on March 17, 2016
 */

#pragma once
#include "DHFrame.hpp"
#include "AxisAngle.hpp"

#include <vector>
#include <armadillo>

namespace BipedLibrary
{
    using namespace arma;
    
    class Chain : public std::vector<DHFrame>
    {
    public:
        Chain(vec3 const posi_body_body = vec3(),
              mat33 const ori_body = mat33());
        
        vec3 posi_body_body(int frame) const;
        mat33 const& ori_body() const;
        vec3 posi_end_last_last() const;
        mat33 ori_end_last() const;
        
        Chain& setPosi_body_body(vec3 const& posi_body_body);
        Chain& setOri_body(mat33 const& ori_body);
        Chain& setPosi_end_last_last(vec3 const& posi_end_last_last);
        Chain& setOri_end_last(mat33 const& ori_end_last);
        
        vec3 position_end_body_body() const;
        vec3 position_base_base(int frame = -1) const;
        vec3 position_body_body(int frame = -1) const;
        vec3 position_pre_pre(int i) const;
        vec3 position_com (int frame) const;
        mat33 orientation_end_body() const;
        mat33 orientation_body(int frame = -1) const;
        mat33 orientation_base(int frame = -1) const;
        mat33 orientation_pre(int i) const;
        mat66 jacobi_base(int frame, vec3 target = {0, 0, 0}) const;
        mat66 jacobi_body(int frame, vec3 target = {0, 0, 0}) const;
        
        bool solveForJointAngles(vec3 const& posi_end_body, AxisAngle ori_end_body);

    private:
        vec3 posi_body_body_;
        mat33 ori_body_;
        vec3 posi_end_last_last_;
        mat33 ori_end_last_;

    };

}
