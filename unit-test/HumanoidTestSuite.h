#pragma once

#include <cxxtest/TestSuite.h>
#include "../include/Humanoid.hpp"
#include <armadillo>

using namespace BipedLibrary;
using namespace arma;

class HumanoidTestSuite : public CxxTest::TestSuite
{
public:
    void testSetAndGet()
{
        Humanoid humanoid;
        Chain myChain;
        myChain.push_back(DHFrame());
        humanoid.setLeftHand(myChain);
        TS_ASSERT_EQUALS(humanoid.leftHand().size(), 1);

        myChain.push_back(DHFrame());
        humanoid.setRightHand(myChain);
        TS_ASSERT_EQUALS(humanoid.rightHand().size(), 2);

        myChain.push_back(DHFrame());
        humanoid.setHead(myChain);
        TS_ASSERT_EQUALS(humanoid.head().size(), 3);

        humanoid.mutableLeftHand().push_back(DHFrame());
        TS_ASSERT_EQUALS(humanoid.leftHand().size(), 2);

        humanoid.mutableRightHand().push_back(DHFrame());
        TS_ASSERT_EQUALS(humanoid.rightHand().size(), 3);

        humanoid.mutableHead().push_back(DHFrame());
        TS_ASSERT_EQUALS(humanoid.head().size(), 4);

        humanoid.calibrate();
    }
};

