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
 * File:   Camera.hpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 8, 2017
 */

#pragma once

#include "Chain.hpp"

#include <vector>

namespace BipedLibrary
{

    class Camera
    {
    public:
        Camera();
        
        vec3 position() const;
        vec3 extrinsicCalibration() const;
        mat33 orientation() const;
        vec2 imageSize() const;
        Angle openAngle() const;

        Camera& setPosition(vec3 const& position);
        Camera& setExtrinsicCalibration(vec3 const& extrinsicCalibration);
        Camera& setOrientation(mat33 const& orientation);
        Camera& setImageSize(float width, float height);
        Camera& setOpenAngle(Angle const& openAngle);
        Camera& setOpenAngle(float openAngle);

        vec3& mutablePosition();
        vec3& mutableExtinsicCalibration();
        mat33& mutableOrientation();
        vec2& mutableImageSize();
        Angle& mutableOpenAngle();


    private:
        vec3 position_;
        vec3 extrinsicCalibration_;
        mat33 orientation_;
        vec2 imageSize_;
        Angle openAngle_;

    };

}
