#!/usr/bin/env bash

# files
rm -rf Testing
rm -rf Makefile
rm -rf CMakeFiles
rm -rf CmakeCache.txt
rm -rf cmake_install.cmake
rm -rf CTestTestfile.cmake

# executables
rm -rf build/Beam
rm -rf build/podcast-tests
rm -rf build/episode-tests
rm -rf build/episodes-repository-tests
rm -rf build/podcasts-repository-tests
rm -rf build/database-manager-tests

# libraries
rm -rf build/libCatch.a
rm -rf build/libbeam-ui.a
rm -rf build/libTestUtils.a
rm -rf build/libbeam-entities.a
rm -rf build/libbeam-database.a