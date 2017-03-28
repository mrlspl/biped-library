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
 * File:   Chain.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on March 17, 2016
 */

#include "Chain.hpp"
#include "Angle.hpp"
#include "Utility.hpp"

#include <stdexcept>
#include <vector>
#include <armadillo>

using namespace BipedLibrary;
using namespace BipedLibrary::Utility;

Chain::Chain(vec3 const posi_body_body, mat33 const ori_body) :
posi_body_body_(posi_body_body),
ori_body_(ori_body)
{

}

vec3 Chain::posi_body_body(int frame) const
{
    return ori_body_ * position_base_base(frame) + posi_body_body_;
}

mat33 const& Chain::ori_body() const
{
    return ori_body_;
}

vec3 Chain::posi_end_last_last() const
{
	return posi_end_last_last_;
}
mat33 Chain::ori_end_last() const
{
	return ori_end_last_;
}

Chain& Chain::setPosi_body_body(vec3 const& posi_body_body)
{
    
    posi_body_body_ = posi_body_body;
    return *this;
}

Chain& Chain::setOri_body(mat33 const& ori_body)
{
    ori_body_ = ori_body;
    return *this;
}

Chain& Chain::setPosi_end_last_last(vec3 const& posi_end_last_last)
{
	posi_end_last_last_ = posi_end_last_last;
	return *this;
}

Chain& Chain::setOri_end_last(mat33 const& ori_end_last)
{
	ori_end_last_ = ori_end_last;
	return *this;
}

vec3 Chain::position_end_body_body() const
{
	mat33 const ori_last_base = orientation_base();
	vec3 const posi_end_base_base = position_base_base() + ori_last_base * posi_end_last_last_;
	return posi_body_body_ + ori_body_ * posi_end_base_base;
}

vec3 Chain::position_base_base(int frame) const
{
    if(frame == -1)
        frame = size() - 1;
   
    if(frame < 0 || (size_t)frame >= size())
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::position_base_base(int)"));
    
    if(frame == 0)
        return position_pre_pre(frame);
    
    return position_base_base(frame - 1) + orientation_base(frame - 1) * position_pre_pre(frame);
}

vec3 Chain::position_pre_pre(int i) const
{
    vec3 output;

    try
    {
        output <<   at(i).r()                       << endr
               << - at(i).d() * at(i).alpha().sin() << endr
               <<   at(i).d() * at(i).alpha().cos() << endr;
    }
    catch(std::out_of_range &)
    {
        throw(std::out_of_range("Out of range index in Chain::position_pre_pre(int)."));
    }
    
    return output;
}

vec3 Chain::position_com(int frame) const
{
    // FIXME: This is not actually COM! Be warned!
    return vec3({at(frame).r() / 2.f, 0.f, 0.f});
}

mat33 Chain::orientation_end_body() const
{
	return ori_body_ * orientation_base() * ori_end_last_;
}

mat33 Chain::orientation_base(int frame) const
{
    if(frame == -1)
        frame = size() - 1;
    
    if(frame < 0 || (size_t)frame >= size())
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::orientation_base(int)"));

    if (frame == 0)
        return orientation_pre(frame);
    else
        return orientation_base(frame-1) * orientation_pre(frame);
    
}

// TODO: This should be in DHFrame class
mat33 Chain::orientation_pre(int i) const
{
    mat33 output;
    Angle theta,alpha;
    theta = at(i).theta();
    alpha = at(i).alpha();

    try
    {
        output  << theta.cos()               << -theta.sin()              << 0            << endr
                << theta.sin() * alpha.cos() << theta.cos() * alpha.cos() << -alpha.sin() << endr
	            << theta.sin() * alpha.sin() << theta.cos() * alpha.sin() <<  alpha.cos() << endr;
    }
    catch(std::out_of_range &)
    {
        throw(std::out_of_range("Out of range index in Chain::orientation_pre(int)."));
    }
    
    return output;

}

mat66 Chain::jacobi_base(int frame, bool com) const
{
    mat66 jacobi={0,0,0,0,0,0,
                   0,0,0,0,0,0,
                   0,0,0,0,0,0,
                   0,0,0,0,0,0,
                   0,0,0,0,0,0,
                   0,0,0,0,0,0};
    vec3 z_i_base={0, 0, 0};
    vec3 matrix={0, 0, 1};
    vec3 r_frame_i_base;
    vec3 temp;
    for (int i=0; i<=frame; i++)
    {
        z_i_base = orientation_base(i)*matrix;
//        std::cout << "z_i_base" << z_i_base << std::endl;
        r_frame_i_base = position_base_base(frame) - position_base_base(i);
//        std::cout << "r_frame_i_base" << r_frame_i_base << std::endl;
        if(com==1)
            r_frame_i_base = r_frame_i_base + (orientation_base(frame) * position_com(i));
        //jacobi.col(i)={cpm(z_i_base) * r_frame_i_base, r_frame_i_base};
//        std::cout << "cpm(z_i_base)" << cpm(z_i_base) << std::endl;
        temp = crossProductMatrix(z_i_base) * r_frame_i_base;
        for(int j=0; j<=2; j++)
            jacobi(j,i) = temp(j);  
        for(int j=0; j<=2; j++)
            jacobi(j+3,i) = z_i_base(j);
    }
    return jacobi;
}
