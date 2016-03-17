ACLOCAL_AMFLAGS = -I tools/m4
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/tools/cxxtest

lib_LTLIBRARIES = libbipedlibrary.la
libbipedlibrary_la_SOURCES = src/Chain.cpp src/DHFrame.cpp

include_HEADERS = include/Chain.hpp include/DHFrame.hpp include/Angle.hpp

bin_PROGRAMS = testrunner
nodist_testrunner_SOURCES = unit-test/main.cpp
testrunner_LDADD = libbipedlibrary.la 

unit-test/main.cpp: unit-test/*.h
	tools/cxxtest/bin/cxxtestgen --error-printer -o unit-test/main.cpp unit-test/*.h
	
run-unit-tests : testrunner
	./testrunner

CLEANFILES = unit-test/main.cpp
