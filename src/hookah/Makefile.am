AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I .

lib_LTLIBRARIES = \
libhookah-@VERTICAL3D_API_VERSION@.la \
libhookah_sdl-@VERTICAL3D_API_VERSION@.la \
libhookah_fltk-@VERTICAL3D_API_VERSION@.la

libhookah_@VERTICAL3D_API_VERSION@_la_SOURCES = \
Window.cxx

libhookah_fltk_@VERTICAL3D_API_VERSION@_la_SOURCES = \
drivers/FLTKDriver.cxx \
drivers/FLTKKeyboard.cxx \
drivers/FLTKMouse.cxx \
drivers/FLTKWindow.cxx

libhookah_sdl_@VERTICAL3D_API_VERSION@_la_SOURCES = \
drivers/SDLDriver.cxx \
drivers/SDLMouse.cxx \
drivers/SDLWindow.cxx

libhookah_@VERTICAL3D_API_VERSION@_la_LDFLAGS = -version-info $(VERTICAL3D_SO_VERSION) $(GCOV_LDFLAGS)
libhookah_fltk_@VERTICAL3D_API_VERSION@_la_LDFLAGS = -version-info $(VERTICAL3D_SO_VERSION) $(GCOV_LDFLAGS)
libhookah_sdl_@VERTICAL3D_API_VERSION@_la_LDFLAGS = -version-info $(VERTICAL3D_SO_VERSION) $(GCOV_LDFLAGS)

library_includedir=$(includedir)/vertical3d-$(VERTICAL3D_API_VERSION)/vertical3d/hookah

library_include_HEADERS= \
Hookah.h \
Window.h \
drivers/FLTKKeyboard.h \
drivers/FLTKMouse.h \
drivers/FLTKWindow.h \
drivers/SDLMouse.h \
drivers/SDLWindow.h

AM_CPPFLAGS = $(DEPS_CFLAGS) $(BOOST_CPPFLAGS) $(GCOV_CFLAGS) $(libpng_CFLAGS)
