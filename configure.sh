#!/bin/sh

mkdir -p build
cd build
cmake -DOGRE_ROOT=${OGRE_ROOT} ../
cd -
