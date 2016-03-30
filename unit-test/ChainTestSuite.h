#pragma once

#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../include/Chain.hpp"

#include <iostream>

using namespace BipedLibrary;

class ChainTestSuite : public CxxTest::TestSuite
{
    Chain ch;
public:
    void setUp()
    {
        fvec3 const posi_body_body = {1, 2, 3};
        fmat33 const ori_body = {1,2,3,4,5,6,7,8,9};
        
        ch.setPosi_body_body(posi_body_body);
        ch.setOri_body_body(ori_body);

        double p;
        p = datum::pi;

        DHFrame dhf(0,0.0020,45.11,0);
        ch.addDHFrame(dhf);
        dhf = DHFrame(p/2,-0.3702,0,0);
        ch.addDHFrame(dhf);
        dhf = DHFrame(0,0.4940,102.75,0);
        ch.addDHFrame(dhf);
        dhf = DHFrame(0,-0.1238,100.0,0);
        ch.addDHFrame(dhf);
        dhf = DHFrame(-p/2,-0.0016+(p/4),0,0);
        ch.addDHFrame(dhf);
        dhf = DHFrame(p/2,0.0100,0,0);
        ch.addDHFrame(dhf);
    }
    
    void tearDown()
    {
        ch = Chain();
    }

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

        ch.setPosi_body_body(posi_body_body);
        TS_ASSERT(all(ch.posi_body_body() == posi_body_body));
        
        ch.setOri_body_body(ori_body);
        TS_ASSERT(all(all(ch.ori_body() == ori_body)));
        
        DHFrame dhf(0.1, 0.2, 3, 4);
        ch.addDHFrame(dhf);
        TS_ASSERT_EQUALS(ch.numOfDHFrames(), 7);
        TS_ASSERT_EQUALS(ch.dHFrame(6), dhf);
        TS_ASSERT_EQUALS(ch.mutableDHFrames().size(), size_t(7));
    }
    
    void testPosi_base_base()
    {
        fvec3 posi_base_base;
        posi_base_base << 240.1346 << endr
               << 0.3846 << endr
               << -24.6434 << endr;

        std::cout << ch.position_base_base(5) << std::endl;
        std::cout << posi_base_base << std::endl;
        std::cout << ch.position_base_base(5) - posi_base_base << std::endl;
        
        TS_ASSERT_LESS_THAN(max(abs(ch.position_base_base(5) - posi_base_base)), 0.0001);
    }
    
};

