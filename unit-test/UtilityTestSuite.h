#pragma once

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/Utility.hpp"

using namespace BipedLibrary::Utility;

class UtilityTestSuite : public CxxTest::TestSuite
{
public:
    void testCrossProductMatrix()
    {
        vec3 const i = {1, 0, 0};
        vec3 const j = {0, 1, 0};
        vec3 const k = {0, 0, 1};
        
        // i x j = k
        TS_ASSERT(all(crossProductMatrix(i) * j == k));
        
        // j x k = i
        TS_ASSERT(all(crossProductMatrix(j) * k == i));
        
        // k x i = j
        TS_ASSERT(all(crossProductMatrix(k) * i == j));
    }

    void testIsRotationMatris()
    {
    	mat33 notARotation;
    	notARotation << 1 << 2 << 3 << endr
                	 << 2 << 3 << 4 << endr
                     << 3 << 4 << 5 << endr;

    	mat33 rotation;
    	rotation << 1 << 0 << 0 << endr
                 << 0 << 0 << 1 << endr
                 << 0 << 1 << 0 << endr;

    	TS_ASSERT(!isRotationMatrix(notARotation));
    	TS_ASSERT(isRotationMatrix(rotation));
    }

    void testOrientationConvertions()
    {
    	arma_rng::set_seed_random();

    	for(int i = 0; i < 100; i++)
    	{
    		vec3 const euler = (randu(3, 1) - 0.5f) * 2 * M_PI;

    		mat33 const ori = AxisAngle({0, 0, 1}, euler(2)).rotationMatrix()
    	    				* AxisAngle({0, 1, 0}, euler(1)).rotationMatrix()
		    				* AxisAngle({1, 0, 0}, euler(0)).rotationMatrix();

    		vec3 newEuler;
    		try
    		{
    			newEuler = Utility::rotationMatrixToEulerAngles(ori);
    		}
    		catch(std::domain_error)
    		{
    			std::cout << ori << std::endl;
    			TS_FAIL("Orientation Matrix is not valid.");
    		}

    		mat33 newOri = AxisAngle({0, 0, 1}, newEuler(2)).rotationMatrix()
						* AxisAngle({0, 1, 0}, newEuler(1)).rotationMatrix()
						* AxisAngle({1, 0, 0}, newEuler(0)).rotationMatrix();

    		TS_ASSERT_LESS_THAN(max(max(abs(newOri - ori))), 0.001);

    		AxisAngle const axisAngle = Utility::eulerAnglesToAxisAngle(euler);
    		AxisAngle const newAxisAngle = Utility::eulerAnglesToAxisAngle(newEuler);

    		TS_ASSERT_LESS_THAN_EQUALS(max(abs(newAxisAngle.asAVector() - axisAngle.asAVector())), 0.0001);
    	}
    }
};

