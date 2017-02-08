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
        myChain.addDHFrame(DHFrame());
        biped.setLeftLeg(myChain);
        TS_ASSERT_EQUALS(biped.leftLeg().numOfDHFrames(), 1);
        
        myChain.addDHFrame(DHFrame());
        biped.setRightLeg(myChain);
        TS_ASSERT_EQUALS(biped.rightLeg().numOfDHFrames(), 2);
    }
};

