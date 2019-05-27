AUTOMAKE_OPTIONS = subdir-objects
noinst_LIBRARIES = \
    libmsghandling.a
libmsghandling_a_SOURCES = \
    socket.cpp \
    endpoint.cpp \
    basemessage.cpp

LDFLAGS += -L/usr/local/lib

CLEANFILES = *~

AM_CPPFLAGS = \
    -g3 -g -ggdb -O3 -Wall
