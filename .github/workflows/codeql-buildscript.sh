#!/usr/bin/env bash

mkdir build
cd build
cmake -DNO_SDL2=1 ../
make
