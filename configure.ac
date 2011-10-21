AC_INIT([Vertical3D], [0.1], [sigsegv@quantumfish.com], [Vertical3D], [http://www.quantumfish.com/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
AC_PROG_CXX
AC_PROG_LIBTOOL
LT_INIT([disable-static])

AC_HEADER_STDC
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([iostream])

# need at least boost 1.41 for property tree support
BOOST_REQUIRE([1.41])
BOOST_TEST
# need boost signals for libv3dcommand
BOOST_SIGNALS

# gcov support (for code coverage reports)

AC_PATH_PROG([GCOV], [gcov], [enable_gcov=no])

AC_MSG_CHECKING([whether to build with gcov testing])

AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov],
                              [Whether to enable coverage testing (requires gcc and gcov)])],
              [],
              [enable_gcov=no])

AS_IF([test "x$enable_gcov" = "xyes" && test "x$GCC" = "xyes"],
      [
        GCOV_CFLAGS="-g -O0 -fprofile-arcs -ftest-coverage"
        GCOV_LDFLAGS="-lgcov"
      ]
)

AM_CONDITIONAL([GCOV_ENABLED], [test "x$enable_gcov" = "xyes"])
AC_SUBST([GCOV_CFLAGS])
AC_SUBST([GCOV_LDFLAGS])
AC_MSG_RESULT([$enable_gcov])


AC_SUBST([VERTICAL3D_SO_VERSION], [0:1:0])
AC_SUBST([VERTICAL3D_API_VERSION], [1.0])

V3D_CONFIG_NICE([config.nice])

AC_CONFIG_FILES([
Makefile 
src/3dtypes/Makefile
src/command/Makefile
src/tests/Makefile
])

AC_OUTPUT

