#!/bin/bash

if [ ! -d cmake-build-watcom ] 
then
	mkdir cmake-build-watcom
fi

cd cmake-build-watcom
cmake -G "Watcom WMake" -D WATCOM=1 -D CMAKE_SYSTEM_NAME=DOS ..
wmake
