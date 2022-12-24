AUTOMAKE_OPTIONS = subdir-objects
noinst_LIBRARIES = \
    libmsghandling.a
libmsghandling_a_SOURCES = \
    endpoint.cpp \
    socket.cpp \
    timestruct.cpp

LDFLAGS += -L/usr/local/lib

CLEANFILES = *~

AM_CPPFLAGS = \
    -g3 -g -ggdb -O3 -Wall
