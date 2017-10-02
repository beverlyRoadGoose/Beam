#!/usr/bin/env bash

export CXX=g++
export CC=gcc
mkdir lib && cd lib && mkdir catch && cd catch && touch catch.hpp && touch catch.cpp
curl -L https://github.com/philsquared/Catch/releases/download/v1.10.0/catch.hpp >> catch.hpp
cd .. && curl -L https://sqlite.org/2017/sqlite-autoconf-3200100.tar.gz | tar zx
mv sqlite-autoconf-3200100/ sqlite/
cd sqlite && mkdir build-debug && cd build-debug && ../configure && make && cd ../../..