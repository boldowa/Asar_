#!/bin/sh
########################################
# build script
########################################

cd `dirname "$0"`

if test -r Makefile ; then
	echo "Cleaning..."
	make clean
fi

which cmake
if test ! $? ; then
	echo "Error: cmake isn't installed. pls install it."
	exit
fi

rm -rf CMake* cmake_*

echo "Build start..."
cmake ..; cmake ..; make -j2
sync

