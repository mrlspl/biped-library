#pragma once

#include <cxxtest/TestSuite.h>
#include "../src/Utility.hpp"

using namespace BipedLibrary::Utility;

class UtilityTestSuite : public CxxTest::TestSuite
{
public:
    void testCrossProductMatrix()
    {
        vec3 i = {1, 0, 0};
        vec3 j = {0, 1, 0};
        vec3 k = {0, 0, 1};
        
        // i x j = k
        TS_ASSERT(all(crossProductMatrix(i) * j == k));
        
        // j x k = i
        TS_ASSERT(all(crossProductMatrix(j) * k == i));
        
        // k x i = j
        TS_ASSERT(all(crossProductMatrix(k) * i == j));
    }
};

