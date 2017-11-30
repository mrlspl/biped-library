#pragma once

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/Utility.hpp"
#include "Angle.hpp"

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

    void testrotationMatrixToAxisAngle()
    {
		mat33 newrot1 = eye(3 , 3);

		AxisAngle const newAxisAngle1 = Utility::rotationMatrixToAxisAngle(newrot1);
    	TS_ASSERT_LESS_THAN((newAxisAngle1.angle().abs().toFloat() - 0), 0.0001);

    	mat33 newrot2;
		newrot2 << -1 <<  0 <<  0 << endr
                <<  0 << -1 <<  0 << endr
                <<  0 <<  0 <<  1 << endr;
		AxisAngle newAxisAngle2 = Utility::rotationMatrixToAxisAngle(newrot2);
		TS_ASSERT_LESS_THAN((newAxisAngle2.angle() - M_PI).abs().toFloat(), 0.00001);
		TS_ASSERT_LESS_THAN(max(abs(newAxisAngle2.axis() - vec3{0, 0, 1})), 0.00001);


		newrot2 << -1 << 0 <<  0 << endr
                <<  0 <<  1 <<  0 << endr
                <<  0 <<  0 << -1 << endr;
		newAxisAngle2 = Utility::rotationMatrixToAxisAngle(newrot2);
		TS_ASSERT_LESS_THAN((newAxisAngle2.angle() - M_PI).abs().toFloat(), 0.00001);
		TS_ASSERT_LESS_THAN(max(abs(newAxisAngle2.axis() - vec3{0, 1, 0})), 0.00001);


		newrot2 <<  1 <<  0 <<  0 << endr
                <<  0 << -1 <<  0 << endr
                <<  0 <<  0 << -1 << endr;
		newAxisAngle2 = Utility::rotationMatrixToAxisAngle(newrot2);
		TS_ASSERT_LESS_THAN((newAxisAngle2.angle() - M_PI).abs().toFloat(), 0.00001);
		TS_ASSERT_LESS_THAN(max(abs(newAxisAngle2.axis() - vec3{1, 0, 0})), 0.00001);

		mat33 newrot3;
        newrot3 <<  0.573151898847004 << -0.608966799623401 <<  0.548321381859677 << endr
               <<  0.740340592718823 <<  0.671651524741135 << -0.027929126116849 << endr
               << -0.351272981626563 <<  0.421952208513407 <<  0.835801188148140 << endr;

		AxisAngle const newAxisAngle3 = Utility::rotationMatrixToAxisAngle(newrot3);

    	TS_ASSERT_LESS_THAN((newAxisAngle3.angle() - Angle(1.f)).abs().toFloat() , 0.0001);
		TS_ASSERT_LESS_THAN(max(abs(newAxisAngle3.axis() - vec3{0.2673f, 0.5345f, 0.8017f})), 0.0001);


		mat33 newrot4;
        newrot4 <<  0.931079941628314	<<    0.349876707321035	<<   -0.103326821162788 << endr
        	    << -0.337843493858078	<<    0.933814901642773	<<    0.117692408963642 << endr
        	    <<  0.137665957866069	<<   -0.074672746997078	<<    0.987659893334101 << endr;

		AxisAngle const newAxisAngle4 = Utility::rotationMatrixToAxisAngle(newrot4);

    	TS_ASSERT_LESS_THAN((newAxisAngle4.angle() - (0.386385069601159)).abs().toFloat() , 0.00001);
		TS_ASSERT_LESS_THAN(max(abs(newAxisAngle4.axis() - vec3{-0.255232860147416,  -0.319752690965349,  -0.912477070244173})), 0.0001);


		mat33 newrot5;
        newrot5 <<  0.609025728228435	<<   -0.792245977227935	<<	-0.037867848129747 << endr
        	    <<	0.361886524232915  <<	0.320044380201132		<<	-0.875562526767959	<< endr
        	    <<	0.705780281627677 	<<   0.519536241534531		<<    0.481618404753939 << endr;

		AxisAngle const newAxisAngle5 = Utility::rotationMatrixToAxisAngle(newrot5);

    	TS_ASSERT_LESS_THAN((newAxisAngle5.angle() - (1.36398088)).abs().toFloat() , 0.000001);
		TS_ASSERT_LESS_THAN(max(abs(newAxisAngle5.axis() - vec3{0.7127f, -0.3799f, 0.5896f})), 0.0001);



    }
};

