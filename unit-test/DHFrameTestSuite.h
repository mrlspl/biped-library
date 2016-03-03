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
        
        std::vector<DHFrame* > fellows;
        fellows.push_back(new DHFrame(0, 0, 1, 2));
        fellows.push_back(new DHFrame(0, 0, 2, 2));
        fellows.push_back(new DHFrame(0, 0, 3, 2));
        
        dhf.setFellows(fellows);
        TS_ASSERT_EQUALS(dhf.fellows().size(), fellows.size());
        TS_ASSERT_EQUALS(dhf.fellows().at(1)->r(), 2);

        TS_ASSERT_EQUALS(dhf.fellow(1)->r(), 2);
        
        dhf.mutableFellow(1)->setR(23);
        TS_ASSERT_EQUALS(dhf.fellow(1)->r(), 23);
        
        dhf.mutableFellows().at(1)->setR(43);
        TS_ASSERT_EQUALS(dhf.fellow(1)->r(), 43);
        
        for(DHFrame* dhfp : fellows)
            delete dhfp;
        
    }
};

