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

fvec3 Chain::posi_base_base(int i) const
{
    if(i == -1)
        i = dHFrames_.size() - 1;
    
    if(i < 0 || (size_t)i >= dHFrames_.size())
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::posi_base_base(int)"));
    
    // TODO: Implement recursive forward kinematics (for position) here.
}

fmat33 Chain::ori_base_base(int i) const
{
    if(i == -1)
        i = dHFrames_.size() - 1;
    
    if(i < 0 || (size_t)i >= dHFrames_.size())
        throw(std::out_of_range("Index out of range in BipedLibrary::Chain::ori_base_base(int)"));

    // TODO: Implement recursive forward kinematics (for orientation) here.
}
