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
 * File:   Utility.cpp
 * Author: <a href="a.sharpasand@mrl-spl.ir">Mohammad Ali Sharpasand</a>
 *
 * Created on February 22, 2017
 */

#include "Utility.hpp"
#include "Angle.hpp"

#include <stdexcept>
#include <cmath>

using namespace BipedLibrary::Utility;

mat33 BipedLibrary::Utility::crossProductMatrix(vec3 vector)
{
    mat33 cpm_vector;
    cpm_vector << 0 << -1 * vector(2) << vector(1) << endr
            << vector(2) << 0 << -1 * vector(0) << endr
            << -1 * vector(1) << vector(0) << 0 << endr;
    return cpm_vector;
}

bool BipedLibrary::Utility::isRotationMatrix(mat33 const& ori)
{
    mat33 shouldBeZero = abs((ori.t() * ori) - eye(3, 3));
    return  all(all(shouldBeZero < 1e-6));
}

vec3 BipedLibrary::Utility::rotationMatrixToEulerAngles(mat33 const& ori)
{
    if(!isRotationMatrix(ori))
    	throw(std::domain_error("Not a rotation matrix in BipedLibrary::Utility::rotationMatrixToEulerAngles"));

    float rx, ry, rz;

    if(ori(2, 0) < -0.999999f)
    {
    	rz = 0;
    	ry = M_PI_2;
    	rx = std::atan2(ori(0, 1), ori(0, 2));
        return vec3{rx, ry, rz};
    }

    if(ori(2, 0) > 0.999999f)
    {
    	rz = 0;
    	ry = -M_PI_2;
    	rx = std::atan2(-ori(0, 1), -ori(0, 2));
        return vec3{rx, ry, rz};
    }

    ry = - std::asin(ori(2, 0));
    rx = std::atan2(ori(2, 1) / std::cos(ry), ori(2, 2) / std::cos(ry));
    rz = std::atan2(ori(1, 0) / std::cos(ry), ori(0, 0) / std::cos(ry));

    return vec3{rx, ry, rz};
}

BipedLibrary::AxisAngle BipedLibrary::Utility::eulerAnglesToAxisAngle(vec3 const& euler)
{
	double c1 = std::cos(euler(2) / 2);
	double s1 = std::sin(euler(2) / 2);
	double c2 = std::cos(euler(1) / 2);
	double s2 = std::sin(euler(1) / 2);
	double c3 = std::cos(euler(0) / 2);
	double s3 = std::sin(euler(0) / 2);
	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;
	double w = c1c2 * c3 - s1s2 * s3;
	double x = c1c2 * s3 + s1s2 * c3;
	double y = s1 * c2 * c3 + c1 * s2 * s3;
	double z = c1 * s2 * c3 - s1 * c2 * s3;
	double angle = 2 * std::acos(w);

	return AxisAngle(vec3{x, y, z}, angle);
}

BipedLibrary::AxisAngle BipedLibrary::Utility::rotationMatrixToAxisAngle(mat33 const& rot)
{
    if(!isRotationMatrix(rot))
    	throw(std::domain_error("Not a rotation matrix in BipedLibrary::Utility::rotationMatrixToAxisAngle"));

	Angle theta = std::acos((trace(rot) - 1) / 2);

	vec3 axis = vec3{
		rot(2 , 1) - rot(1 , 2),
		rot(0 , 2) - rot(2 , 0),
		rot(1 , 0) - rot(0 , 1)
	};
	axis = normalise(axis);

	if(!theta.isBetween( M_PI - 0.0001 , (-1 * M_PI) + 0.0001))
		return AxisAngle(axis, theta);

	double x=1;
	double y=0;
	double z=0;
	double epsilon = 0.0001;
	// Singularity at angle = 180 degree
	double xx = (rot(0, 0) + 1) / 2;
	double yy = (rot(1, 1) + 1) / 2;
	double zz = (rot(2, 2) + 1) / 2;
	double xy = (rot(0, 1) + rot(1, 0)) / 4;
	double xz = (rot(0, 2) + rot(2, 0)) / 4;
	double yz = (rot(1, 2) + rot(2, 1)) / 4;
	if ((xx > yy) && (xx > zz)) { // m[0][0] is the largest diagonal term so base result on this
		if (xx< epsilon) {
			x = 0;
			y = 0.7071;
			z = 0.7071;
		} else {
			x = sqrt(xx);
			y = xy/x;
			z = xz/x;
		}
	} else if (yy > zz) { // m[1][1] is the largest diagonal term so base result on this
		if (yy< epsilon) {
			x = 0.7071;
			y = 0;
			z = 0.7071;
		} else {
			y = sqrt(yy);
			x = xy/y;
			z = yz/y;
		}
	} else { // m[2][2] is the largest diagonal term so base result on this
		if (zz< epsilon) {
			x = 0.7071;
			y = 0.7071;
			z = 0;
		} else {
			z = sqrt(zz);
			x = xz/z;
			y = yz/z;
		}
	}

	axis = vec3{
		x,
		y,
		z
	};

	return AxisAngle(axis, theta);
}
