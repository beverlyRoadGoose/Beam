#!/usr/bin/env bash

source .env
cmake -DCMAKE_PREFIX_PATH=lib/wxWidgets/build-debug/ . && make && make test