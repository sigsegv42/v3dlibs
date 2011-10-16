AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I .

bin_PROGRAMS = unit_tests
unit_tests_SOURCES = \
TestMain.cxx \
Color3Test.cxx \
Color4Test.cxx \
Vector2Test.cxx \
Vector3Test.cxx \
AABBoxTest.cxx

AM_CPPFLAGS = $(DEPS_CFLAGS) $(BOOST_CPPFLAGS) $(GCOV_CFLAGS)
AM_LDFLAGS = $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS) $(GCOV_LDFLAGS)

unit_tests_LDADD = $(DEPS_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIBS) $(top_builddir)/src/3dtypes/.libs/libv3dtypes-@VERTICAL3D_API_VERSION@.la
