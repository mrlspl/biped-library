#pragma once

#include <cxxtest/TestSuite.h>
#include <armadillo>
#include <iostream>
#include "../include/Chain.hpp"

using namespace BipedLibrary;

class ChainTestSuite : public CxxTest::TestSuite
{
    Chain ch;
public:
    void setUp()
    {
        vec3 const posi_body_body = {0, 0, 0};
        mat33 const ori_body = {1,0,0,0,1,0,0,0,1};
        
        ch.setPosi_body_body(posi_body_body);
        ch.setOri_body(ori_body);

        double p;
        p = datum::pi;
//----------------data88-----------------------
        DHFrame dhf(0,0.0020,45.11,0);
        ch.push_back(dhf);
        dhf = DHFrame(p/2,-0.3702,0,0);
        ch.push_back(dhf);
        dhf = DHFrame(0,0.4940,102.75,0);
        ch.push_back(dhf);
        dhf = DHFrame(0,-0.1238,100.0,0);
        ch.push_back(dhf);
        dhf = DHFrame(-p/2,-0.0016+(p/4),0,0);
        ch.push_back(dhf);
        dhf = DHFrame(p/2,0.0100,0,0);
        ch.push_back(dhf);

        
    }
    
    void tearDown()
    {
        ch = Chain();
    }

    void testConstructor()
    {
        vec3 const posi_body_body = {0, 0, 0};
        vec3 const result={2.4013e+02, 3.9005e-01, -2.4827e+01}; // data88
        mat33 const ori_body = {1,0,0,0,1,0,0,0,1};
        
        Chain ch(posi_body_body, ori_body);
        
//        TS_ASSERT(all(ch.posi_body_body(5) == result));
//        TS_ASSERT(all(all(ch.ori_body() == ori_body)));
        
    }
    
    void testSetAndGet()
    {
        vec3 const posi_body_body = {1, 2, 3};
        vec3 const result={2.4013e+02, 3.9005e-01, -2.4827e+01};  ///data88
//        vec3 const result={239.0377 , -4.3279 , -8.2007 };  ///data200
        mat33 const ori_body = {3,2,1,1,2,3,4,5,1};
        

        ch.setOri_body(ori_body);
        TS_ASSERT(all(all(ch.ori_body() == ori_body)));
        
        ch.setPosi_body_body(posi_body_body);
        TS_ASSERT_EQUALS(all(ch.posi_body_body(5)),all(result));

        ch.setOri_end_last(ori_body);
        TS_ASSERT(all(all(ch.ori_end_last() == ori_body)));
        
//        DHFrame dhf(0.1, 0.2, 3, 4);
//        ch.addDHFrame(dhf);
//        TS_ASSERT_EQUALS(ch.numOfDHFrames(), 7);
//        TS_ASSERT_EQUALS(ch.dHFrame(6), dhf);
//        TS_ASSERT_EQUALS(ch.mutableDHFrames().size(), size_t(7));
    }
    
    void testPosi_base_base()
    {
        vec3 const posi_base_base ={240.1346, 0.3846, -24.8181}; //data88
        
        TS_ASSERT_LESS_THAN(max(abs(ch.position_base_base(5) - posi_base_base)), 0.01);
    }
    void testJacobi_base()
    {   
        mat66 jacob;
        jacob << -0.384 << 24.8180 << -12.3527 << 0 << 0 << 0 << endr
              << 195.0246 << 0.0489 << -0.0244 << 0 << 0 << 0 << endr
              << 0 <<195.0250 << 99.2341 << 0 << 0 << 0 << endr
              << 0 << 0.0020 << 0.0020 << 0.0020 << 0 << 0.7074 <<endr
              << 0 << -1 << -1 << -1 << 0 << -0.7069 << endr
              << 1 << 0 << 0 << 0 << 1 << 0 << endr;
             
       TS_ASSERT_LESS_THAN(max(abs(all(all(ch.jacobi_base(5,0) - jacob)))), 0.01);
    }
};

