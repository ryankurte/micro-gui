#!/bin/bash

echo "System information"
echo `uname -a`

echo "Package information"
echo `ls /etc/`
echo `ls /etc/apt/`

echo "SDL information"
echo `pkg-config --cflags sdl2`
echo `apt-cache search sdl2`
