#pragma once

#include <cxxtest/TestSuite.h>
#include "../include/Biped.hpp"
#include <armadillo>

using namespace BipedLibrary;
using namespace arma;

class BipedTestSuite : public CxxTest::TestSuite
{
public:
    void testSetAndGet()
    {
        Biped biped;
        Chain myChain;
        myChain.push_back(DHFrame());
        biped.setLeftLeg(myChain);
        TS_ASSERT_EQUALS(biped.leftLeg().size(), 1);
        
        myChain.push_back(DHFrame());
        biped.setRightLeg(myChain);
        TS_ASSERT_EQUALS(biped.rightLeg().size(), 2);
    }
};

