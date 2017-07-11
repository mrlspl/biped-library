#pragma once

#include <cxxtest/TestSuite.h>
#include <armadillo>
#include <iostream>
#include "../include/Chain.hpp"
#include "../src/Utility.hpp"

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
             
       TS_ASSERT_LESS_THAN(max(abs(all(all(ch.jacobi_base(5) - jacob)))), 0.01);
    }

    void testJacobian()
    {
    	arma_rng::set_seed_random();

    	vec3 const initialPosi = ch.position_end_body_body();
    	mat33 const initialOri = ch.orientation_body();
    	mat66 const initialJacobi = ch.jacobi_body(5, ch.posi_end_last_last());

    	vec6 const perturbation = randu(6, 1) * 0.01;
    	int i = 0;
    	for(DHFrame & frame : ch)
    	{
    		frame.setTheta(frame.theta() + perturbation(i));
			i++;
    	}

    	vec3 const newPosi = ch.position_end_body_body();
    	mat33 const newOri = ch.orientation_body();

    	i = 0;
    	for(DHFrame & frame : ch)
		{
			frame.setTheta(frame.theta() - 2 * perturbation(i));
			i++;
		}

    	vec3 const newPosi2 = ch.position_end_body_body();
    	mat33 const newOri2 = ch.orientation_body();

    	vec3 const deltaPosi = (newPosi - newPosi2) / 2;
    	vec3 const diffPosi  = initialJacobi(span(0, 2), span::all) * perturbation;
    	mat33 const deltaOri = (newOri * newOri2.t() + eye(3, 3)) / 2;
    	vec3 const rotationVector = initialJacobi(span(3, 5), span::all) * perturbation;
    	mat33 const diffOri  = AxisAngle(rotationVector, norm(rotationVector)).rotationMatrix();

    	TS_ASSERT_LESS_THAN(max(abs((diffPosi - deltaPosi) / deltaPosi)), 0.01);
    	TS_ASSERT_LESS_THAN(max(max(abs((diffOri - deltaOri)))), 0.01);
    }

//    void testSolveForJointAngles()
//    {
//    	vec3 const posi_end_body = {40, 100, 200};
//    	AxisAngle const ori_end_body = AxisAngle({0, 0, 0}, 0);
//
//    	ch.solveForJointAngles(posi_end_body, ori_end_body);
//
//    	vec3 const resultPosi = ch.position_end_body_body();
//    	mat33 const resultOri = ch.orientation_end_body();
//    	vec3 const resultAxisAngle = Utility::eulerAnglesToAxisAngle(Utility::rotationMatrixToEulerAngles(ch.orientation_end_body())).asAVector();
//
//    	TS_ASSERT_LESS_THAN(max(abs((resultPosi - posi_end_body) / posi_end_body)), 0.01);
//    	TS_ASSERT_LESS_THAN(max(max(abs(resultOri - ori_end_body.rotationMatrix()))), 0.01);
//    }
};

