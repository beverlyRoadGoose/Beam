#!/usr/bin/env bash

echo ---------- starting dependencies setup ----------
echo

# create a libraries directory if it doesnt exist
if [ ! -d "lib" ]; then
    echo libraries directory doesn\'t exist, creating it.
    mkdir lib
    echo create libraries directory \(lib\)
    echo
fi

# step into libraries directory
cd lib


#############################################
# Catch
#############################################

echo ---------- setting up Catch ----------

if [ -d "catch" ]; then
    echo removing old catch.
    echo
    rm -rf catch
fi

mkdir catch
cd catch

touch catch.cpp
touch catch.hpp

echo downloading catch.hpp v1.10.0
curl -L https://github.com/philsquared/Catch/releases/download/v1.10.0/catch.hpp >> catch.hpp

# back to lib dir
cd ..

echo ---------- Catch successfully setup ----------
echo


###############################################
# Sqlite
###############################################

echo ---------- setting up sqlite ----------
echo

if [ -d "sqlite" ]; then
    echo removing old sqlite.
    rm -rf sqlite
fi

echo downloading sqlite tar
curl -L https://sqlite.org/2017/sqlite-autoconf-3200100.tar.gz | tar zx
mv sqlite-autoconf-3200100/ sqlite/
cd sqlite
mkdir build-debug
cd build-debug
../configure
make

# back to lib dir
cd ../..

echo ---------- sqlite successfuly setup ----------
echo


#################################################
# wxWidgets
#################################################

echo ---------- setting up wxWidgets ----------
echo

if [ -d "wxWidgets" ]; then
    echo removing old wxWidgets.
    echo
    rm -rf wxWidgets
fi

echo downloading wxWidgets zip
curl -L https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3.1/wxWidgets-3.0.3.1.zip -o wxWidgets.zip
mkdir wxWidgets
unzip wxWidgets.zip -d wxWidgets
rm -rf wxWidgets.zip
cd wxWidgets
mkdir build-debug
cd build-debug

echo ---------- building wxWidgets: this could take 20 minutes or more ----------
../configure --enable-debug --enable-monolithic --with-macosx-version-min=10.9
make

echo ---------- finished building wxWidgets ----------
echo

echo ---------- wxWidgets setup succesfully ----------
echo

# back to project root dir
cd ../../..

echo ---------- dependencies setup complete ----------