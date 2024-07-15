#!/bin/sh
set -eux

headers=-I./src/headers/
src=./src/src/*.cpp
libs="-lsfml-graphics -lsfml-window -lsfml-system"

g++ src/main.cpp $src -g -o build/main $headers $libs
./build/main