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

AC_SUBST([VERTICAL3D_SO_VERSION], [0:1:0])
AC_SUBST([VERTICAL3D_API_VERSION], [1.0])

AC_CONFIG_FILES([
Makefile 
src/3dtypes/Makefile
src/command/Makefile
src/tests/Makefile
])

AC_OUTPUT

