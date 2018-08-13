cmake_minimum_required(VERSION 3.0)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#This is our library name 
project(mycustomlib)

#Add source files that you need just add them end of the line 
file(GLOB SOURCES ./src/AxisAngle.cpp ./src/Biped.cpp ./src/Calibrator.cpp ./src/Camera.cpp ./src/Chain.cpp
./src/DHFrame.cpp ./src/Humanoid.cpp ./src/Utility.cpp)

#Set includes that program needs to run with it 
set ( Eigen_INCLUDE_DIRS /usr/include/eigen3/)
include_directories(include src ${Eigen_INCLUDE_DIRS})

file(GLOB UNIT_TEST ./unit-test/AngleTestSuit.h ./unit-test/AxisAngleTestSuite.h ./unit-test/BipedTestSuite.h ./unit-test/ChainTestSuite.h ./unit-test/DHFrameTestSuite.h ./unit-test/HumanoidTestSuite.h ./unit-test/UtilityTestSuite.h)


add_library(mycustomlib SHARED ${SOURCES})

install(TARGETS mycustomlib DESTINATION lib/mycustomlib)

file(GLOB HEADERS ./include/Angle.hpp ./include/AxisAngle.hpp ./include/Biped.hpp ./include/Calibrator.hpp
./include/Camera.hpp ./include/Chain.hpp ./include/DHFrame.hpp ./include/Humanoid.hpp ./include/Utility.hpp
)
install(FILES ${HEADERS} DESTINATION include/mycustomlib)





find_package(PythonInterp)


find_package(CxxTest REQUIRED)

if(CXXTEST_FOUND)
	include_directories(${CXXTEST_INCLUDE_DIR})
	enable_testing()
	CXXTEST_ADD_TEST(testrunner testrunner.cpp
                        ${UNIT_TEST})
	target_link_libraries(testrunner mycustomlib armadillo ceres glog pthread cholmod lapack blas cxsparse)
endif()
	


  #-----------------------------------------------------------------------
  # CPM configuration
  #-----------------------------------------------------------------------
  set(CPM_MODULE_NAME biped-library)
  set(CPM_LIB_TARGET_NAME ${CPM_MODULE_NAME})
  
  if ((DEFINED CPM_DIR) AND (DEFINED CPM_UNIQUE_ID) AND (DEFINED CPM_TARGET_NAME))
    set(CPM_LIB_TARGET_NAME ${CPM_TARGET_NAME})
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CPM_DIR})
    include(CPM)
  else()
    set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
    find_package(Git)
    if(NOT GIT_FOUND)
      message(FATAL_ERROR "CPM requires Git.")
    endif()
    if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
      message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
      execute_process(
        COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
        RESULT_VARIABLE error_code
        OUTPUT_QUIET ERROR_QUIET)
      if(error_code)
        message(FATAL_ERROR "CPM failed to get the hash for HEAD")
      endif()
    endif()
    include(${CPM_DIR}/CPM.cmake)
  endif()
  
  # Include CPM modules or externals here (with CPM_AddModule).
  
  CPM_InitModule(${CPM_MODULE_NAME})



##############################################################################################################
