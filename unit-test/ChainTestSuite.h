#pragma once

#include <cxxtest/TestSuite.h>
#include "../include/Chain.hpp"

using namespace BipedLibrary;

class ChainTestSuite : public CxxTest::TestSuite
{
public:
    void testConstructor()
    {
        fvec3 const posi_body_body = {1, 2, 3};
        fmat33 const ori_body = {1,2,3,4,5,6,7,8,9};
        
        Chain ch(posi_body_body, ori_body);
        
        TS_ASSERT(all(ch.posi_body_body() == posi_body_body));
        TS_ASSERT(all(all(ch.ori_body() == ori_body)));
    }
    
    void testSetAndGet()
    {
        fvec3 const posi_body_body = {1, 2, 3};
        fmat33 const ori_body = {1,2,3,4,5,6,7,8,9};

        Chain ch;

        ch.setPosi_body_body(posi_body_body);
        TS_ASSERT(all(ch.posi_body_body() == posi_body_body));
        
        ch.setOri_body_body(ori_body);
        TS_ASSERT(all(all(ch.ori_body() == ori_body)));
    }
};

