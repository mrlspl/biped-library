ACLOCAL_AMFLAGS = -I tools/m4
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_srcdir)/tools/cxxtest -fopenmp -I/usr/include/eigen3
AM_LDFLAGS = -fopenmp

lib_LTLIBRARIES = libbipedlibrary.la
libbipedlibrary_la_SOURCES = src/Chain.cpp \
                             src/DHFrame.cpp \
                             src/Biped.cpp \
                             src/Humanoid.cpp \
			     src/AxisAngle.cpp \
			     src/Utility.cpp
			     
pkginclude_HEADERS = include/Chain.hpp \
                     include/DHFrame.hpp \
                     include/Angle.hpp \
                     include/Biped.hpp \
                     include/Humanoid.hpp \
		     include/AxisAngle.hpp

libbipedlibrary_la_LIBADD = -larmadillo

bin_PROGRAMS = testrunner
nodist_testrunner_SOURCES = unit-test/main.cpp
testrunner_LDADD = libbipedlibrary.la -larmadillo -lceres -lglog -lpthread -llapack -lblas -lcholmod

unit-test/main.cpp: unit-test/*.h
	tools/cxxtest/bin/cxxtestgen --error-printer -o unit-test/main.cpp unit-test/*.h
	
run-unit-tests : testrunner
	./testrunner

CLEANFILES = unit-test/main.cpp
