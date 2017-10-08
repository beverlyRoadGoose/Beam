#!/usr/bin/env bash

#
#  Copyright 2017 Oluwatobi Adeyinka
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

if [[ "$(uname)" == "Darwin" ]]; then # osx

    brew install wxmac
    brew upgrade boost
    brew upgrade cmake

elif [[ "$(expr substr $(uname -s) 1 5)" == "Linux" ]]; then # linux

    sudo apt-get update
    sudo apt-get install curl
    sudo apt-get install cmake
    sudo apt-get install libboost-dev
    sudo apt-get install libgtk-3-dev
    sudo apt-get install build-essential
    sudo apt-get install sqlite3 libsqlite3-dev

fi
