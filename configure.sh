#!/bin/sh

mkdir build
cd build
cmake -DOGRE_ROOT=${OGRE_ROOT} ../
cd -
