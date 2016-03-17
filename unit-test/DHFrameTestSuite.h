#pragma once

#include <cxxtest/TestSuite.h>
#include "../include/DHFrame.hpp"

using namespace BipedLibrary;

class DHFrameTestSuite : public CxxTest::TestSuite
{
public:
    void testConstructor()
    {
        
        DHFrame dhf(1.57f, -1.57f, 1.f, 2.f);
        TS_ASSERT_EQUALS(dhf.alpha().toFloat(),  1.57f);
        TS_ASSERT_EQUALS(dhf.theta().toFloat(), -1.57f);
        TS_ASSERT_EQUALS(dhf.r(), 1.f);
        TS_ASSERT_EQUALS(dhf.d(), 2.f);
    }
    
    void testSetAndGet()
    {
        DHFrame dhf;
        
        dhf.setAlpha(2.f);
        TS_ASSERT_EQUALS(dhf.alpha().toFloat(), 2.f);
        
        dhf.setTheta(3.f);
        TS_ASSERT_EQUALS(dhf.theta().toFloat(), 3.f);
        
        dhf.setR(27);
        TS_ASSERT_EQUALS(dhf.r(), 27);
        
        dhf.setD(43);
        TS_ASSERT_EQUALS(dhf.d(), 43);
    }
    
    void testIdGenarator()
    {
        TS_ASSERT_DIFFERS(DHFrame(), DHFrame());
    }
};

