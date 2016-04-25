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

#include <vector>
#include <armadillo>

namespace BipedLibrary
{
    
    class Chain
    {
    public:
        Chain(vec3 const posi_body_body = vec3(),
              mat33 const ori_body = mat33());
        
        vec3  posi_body_body(int frame) const;
        mat33 const& ori_body() const;
        DHFrame const& dHFrame(unsigned i);
        size_t numOfDHFrames();
        
        Chain& setPosi_body_body(vec3 const& posi_body_body);
        Chain& setOri_body(mat33 const& ori_body);
        
        Chain& addDHFrame(DHFrame const dHframe);
        
        std::vector<DHFrame> & mutableDHFrames();
        
        vec3 position_base_base(int frame = -1) const;
        vec3 position_pre_pre(int i) const;
        vec3 position_com (int frame) const;
        mat33 orientation_base(int frame = -1) const;
        mat33 orientation_pre(int i) const;
        mat66 jacobi_base(int frame, bool com) const;
        mat33 cpm (vec3 vector) const ;

        
    private:
        vec3 posi_body_body_;
        mat33 ori_body_;
        std::vector<DHFrame> dHFrames_;

    };

}
