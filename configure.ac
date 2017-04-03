AC_CONFIG_MACRO_DIR([tools/m4])
AC_PREREQ([2.69])
AC_INIT([Biped-Library], [0.1], [m.a@sharpasand.com])
LT_INIT([shared])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_SRCDIR([src/DHFrame.cpp])
AM_PROG_AR

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([], [])
AX_CHECK_COMPILE_FLAG([-Wall -Wextra -Wno-unused-variable -Wno-unused-but-set-variable \
-Wno-unused-parameter],\
[CXXFLAGS="$CXXFLAGS -Wall -Wextra -Wno-unused-variable -Wno-unused-but-set-variable \
-Wno-unused-parameter"])
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([armadillo], [arma::ones(10)]) # FIXME: ??
AC_CHECK_LIB([ceres], [Solver::Options()]) # FIXME: no??

# Checks for header files.
AC_CHECK_HEADERS(armadillo) # FIXME: ??

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
