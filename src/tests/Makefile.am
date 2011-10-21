AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I .

bin_PROGRAMS = unit_tests
unit_tests_SOURCES = \
TestMain.cxx \
Color3Test.cxx \
Color4Test.cxx \
Vector2Test.cxx \
Vector3Test.cxx \
AABBoxTest.cxx \
Matrix4Test.cxx \
QuaternionTest.cxx \
ArcBallTest.cxx \
CameraProfileTest.cxx \
CameraTest.cxx \
3dtypesTest.cxx \
Bound2DTest.cxx \
EventInfoTest.cxx \
CommandInfoTest.cxx \
CommandTest.cxx \
BindTest.cxx \
CommandDirectoryTest.cxx

AM_CPPFLAGS = $(DEPS_CFLAGS) $(BOOST_CPPFLAGS) $(GCOV_CFLAGS)
AM_LDFLAGS = $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS) $(GCOV_LDFLAGS) $(BOOST_SIGNALS_LDFLAGS)

unit_tests_LDADD = $(DEPS_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIBS) $(BOOST_SIGNALS_LIBS) \
$(top_builddir)/src/3dtypes/.libs/libv3dtypes-@VERTICAL3D_API_VERSION@.la \
$(top_builddir)/src/command/.libs/libv3dcommand-@VERTICAL3D_API_VERSION@.la \
$(top_builddir)/src/image/.libs/libv3dimage-@VERTICAL3D_API_VERSION@.la
