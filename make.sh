#!/bin/sh

cmd() {
	echo "$*"
	$*
}

CFLAGS="-std=c++98 -Wall -Wno-unused-result -Wno-uninitialized"
CFLAGS="$CFLAGS -fno-rtti -Dstricmp=strcasecmp -DRELEASE"
CFLAGS="$CFLAGS -fdata-sections -ffunction-sections -Wl,--gc-sections"

#For all Linux users out there. I don't think anything uses the Asar library on Linux, but it does no harm.
CXX=g++
cmd $CXX -Dlinux -s -O2 -oasar -DINTERFACE_CLI $CFLAGS *.cpp
cmd $CXX -Dlinux -s -O2 -shared -fpic -olibasar.so -DINTERFACE_LIB $CFLAGS *.cpp

#Win32
CXX=i686-w64-mingw32-g++
cmd $CXX -D_WIN32 -static -s -O2 -oasar.exe -DINTERFACE_CLI $CFLAGS *.cpp
cmd $CXX -D_WIN32 -static -s -O2 -shared -fpic -oasar.dll -DINTERFACE_LIB $CFLAGS *.cpp
