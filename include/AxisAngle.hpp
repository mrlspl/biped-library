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
 * File:   AxisAngle.hpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 22, 2017
 */

#ifndef BIPED_LIBRARY_AXIS_ANGLE_H
#define BIPED_LIBRARY_AXIS_ANGLE_H

#include "Angle.hpp"
#include <armadillo>

namespace BipedLibrary
{
    using namespace arma;

    class AxisAngle
    {
    public:
        AxisAngle(vec3 axis = vec3(), Angle angle = Angle());
        
        mat33 rotationMatrix() const;
        
        vec3 axis() const;
        Angle angle() const;
        vec3 asAVector() const;
        
        AxisAngle& setAxis(vec3 const& axis);
        AxisAngle& setAngle(Angle const& angle);
        
        vec3& mutableAxis();
        Angle& mutableAngle();
    
    private:
        vec3 axis_;
        Angle angle_;
    
    };

}

#endif
