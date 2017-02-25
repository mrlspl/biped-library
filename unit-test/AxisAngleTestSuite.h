#pragma once

#include <cxxtest/TestSuite.h>
#include "../include/AxisAngle.hpp"

using namespace BipedLibrary;

class AxisAngleTestSuite : public CxxTest::TestSuite
{
public:
    void testConstructor()
    {
        AxisAngle axisAngle;
        TS_ASSERT_EQUALS(axisAngle.angle().toFloat(), 0);
        TS_ASSERT(all(axisAngle.axis() == vec3()));
        
        AxisAngle axisAngle2(vec3({1, 2, 3}), Angle(1.234f));
        TS_ASSERT_EQUALS(axisAngle2.angle().toFloat(), 1.234f);
        TS_ASSERT(all(axisAngle2.axis() == vec3({1, 2, 3})));
        
    }
    
    void testGetAndSet()
    {
        AxisAngle axisAngle;
        axisAngle.setAxis(vec3({1, 2, 3})).setAngle(Angle(1.234f));
        TS_ASSERT_EQUALS(axisAngle.angle().toFloat(), 1.234f);
        TS_ASSERT(all(axisAngle.axis() == vec3({1, 2, 3})));
        
    }
    
    void testRotationMatrix()
    {
        mat33 output;
        output << 1 << 0 <<  0 << endr
               << 0 << 0 << -1 << endr
               << 0 << 1 <<  0 << endr;
        
        TS_ASSERT(max(max(abs(AxisAngle(vec3({1, 0, 0}), Angle(M_PI_2)).rotationMatrix() - output)))
                        < 0.0001);
   
        output <<  0 << 0 << 1 << endr
               <<  0 << 1 << 0 << endr
               << -1 << 0 << 0 << endr;
        TS_ASSERT(max(max(abs(AxisAngle(vec3({0, 1, 0}), Angle(M_PI_2)).rotationMatrix() - output)))
                        < 0.0001);
        
        output << 0 << -1 << 0 << endr
               << 1 <<  0 << 0 << endr
               << 0 <<  0 << 1 << endr;
        TS_ASSERT(max(max(abs(AxisAngle(vec3({0, 0, 1}), Angle(M_PI_2)).rotationMatrix() - output)))
                        < 0.0001);

        output <<  0.5731 << -0.6090 <<  0.5483 << endr
               <<  0.7403 <<  0.6716 << -0.0279 << endr
               << -0.3513 <<  0.4219 <<  0.8358 << endr;
        TS_ASSERT(max(max(abs(AxisAngle(vec3({1, 2, 3}), Angle(1.f)).rotationMatrix() - output)))
                        < 0.0001);
                                                                          
    }
};

