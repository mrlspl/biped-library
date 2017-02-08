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
        myChain.addDHFrame(DHFrame());
        humanoid.setLeftHand(myChain);
        TS_ASSERT_EQUALS(humanoid.leftHand().numOfDHFrames(), 1);

        myChain.addDHFrame(DHFrame());
        humanoid.setRightHand(myChain);
        TS_ASSERT_EQUALS(humanoid.rightHand().numOfDHFrames(), 2);

        myChain.addDHFrame(DHFrame());
        humanoid.setHead(myChain);
        TS_ASSERT_EQUALS(humanoid.head().numOfDHFrames(), 3);

        humanoid.mutableLeftHand().addDHFrame(DHFrame());
        TS_ASSERT_EQUALS(humanoid.leftHand().numOfDHFrames(), 2);

        humanoid.mutableRightHand().addDHFrame(DHFrame());
        TS_ASSERT_EQUALS(humanoid.rightHand().numOfDHFrames(), 3);

        humanoid.mutableHead().addDHFrame(DHFrame());
        TS_ASSERT_EQUALS(humanoid.head().numOfDHFrames(), 4);
    }
};

