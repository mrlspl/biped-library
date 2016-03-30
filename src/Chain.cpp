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

#include <stdexcept>
#include <vector>

using namespace BipedLibrary;

Chain::Chain(fvec3 const posi_body_body, fmat33 const ori_body) :
posi_body_body_(posi_body_body),
ori_body_(ori_body)
{

}

fvec3 const& Chain::posi_body_body() const
{
    return posi_body_body_;
}

fmat33 const& Chain::ori_body() const
{
    return ori_body_;
}

DHFrame const& Chain::dHFrame(unsigned i)
{
    try
    {
        return dHFrames_.at(i);
    }
    catch(std::out_of_range &)
    {
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::dHFrame(unsigned)"));
    }
}

size_t Chain::numOfDHFrames()
{
    return dHFrames_.size();
}

Chain& Chain::setPosi_body_body(fvec3 const& posi_body_body)
{
    posi_body_body_ = posi_body_body;
    return *this;
}

Chain& Chain::setOri_body_body(fmat33 const& ori_body)
{
    ori_body_ = ori_body;
    return *this;
}

Chain& Chain::addDHFrame(DHFrame const dHframe)
{
    dHFrames_.push_back(dHframe);
    return *this;
}

std::vector<DHFrame> & Chain::mutableDHFrames()
{
    return dHFrames_;
}

fvec3 Chain::position_base_base(int frame) const
{
    fvec3 result;
    if(frame == -1)
        frame = dHFrames_.size() - 1;
    
    
    if(frame < 0 || (size_t)frame >= dHFrames_.size())
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::position_base_base(int)"));
    
    // TODO: Implement recursive forward kinematics (for position) here.
    
    if(frame==0)
        return position_pre_pre(frame);
    else
    {
        result = orientation_base(frame-1) * position_pre_pre(frame) + position_base_base(frame-1);
        return result;
    }
    
}
fvec3 Chain::position_pre_pre(int i) const
{
	fvec3 output;

	try
	{
		output << dHFrames_.at(i).r() << endr
		       << -dHFrames_.at(i).d() * dHFrames_.at(i).alpha().sin() << endr
		       << dHFrames_.at(i).d() * dHFrames_.at(i).alpha().cos() << endr;
	}
	catch(std::out_of_range &)
	{
		throw(std::out_of_range("Out of range index in Chain::position_pre_pre(int)."));
	}
	return output;
}

fmat33 Chain::orientation_base(int frame) const
{
    if(frame == -1)
        frame = dHFrames_.size() - 1;
    
    if(frame < 0 || (size_t)frame >= dHFrames_.size())
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::orientation_base(int)"));

    // TODO: Implement recursive forward kinematics (for orientation) here.

    if (frame == 0)
    	return orientation_pre(frame);
        //return (conv_to<fmat>::from(eye(3,3)));
    else
    	return orientation_base(frame-1)*orientation_pre(frame);
     
    
}
fmat33 Chain::orientation_pre(int i) const
{

	fmat33 output;
        Angle t,a;
        t = dHFrames_.at(i).theta();
        a = dHFrames_.at(i).alpha();
        
        try
        {

                output  << t.cos() << -(t.sin()) << 0 << endr
	                << t.sin()*a.cos() << t.cos()*a.cos() << -(a.sin()) << endr
	                << t.sin()*a.sin() << t.cos()*a.sin() << a.cos() << endr;
        }
        catch(std::out_of_range &)
	{
		throw(std::out_of_range("Out of range index in Chain::orientation_pre(int)."));
	}
	return output;

	}

