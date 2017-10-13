[![Build Status](https://travis-ci.org/EtherealT/Beam.svg?branch=master)](https://travis-ci.org/EtherealT/Beam)
[![GitHub version](https://badge.fury.io/gh/EtherealT%2FBeam.svg)](https://github.com/EtherealT/Beam/releases)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/a937ca3c85cb4ba6b954523bac851116)](https://www.codacy.com/app/EtherealT/Beam?utm_source=github.com&utm_medium=referral&utm_content=EtherealT/Beam&utm_campaign=badger)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## About
![Beam](https://i.imgur.com/D9Zd3IT.jpg)

Beam is a cross platform desktop podcast client still at the very beginning of development.
I'm building it for my personal use and to learn the [wxWidgets](https://www.wxwidgets.org) GUI library.

## Building / Running

##### Dependencies & Build tools

- [curl](https://curl.haxx.se)
- [curlpp](http://www.curlpp.org)
- [CMake](https://cmake.org)
- [Catch](http://catch-lib.net)
- [SQLite](https://www.sqlite.org)
- [pugixml](https://pugixml.org)
- [RapidJSON](http://rapidjson.org)
- [wxWidgets](https://www.wxwidgets.org)

To build from source, you need the tools listed installed on your system after which you can run the build script
: ```./scripts/build.sh``` to build & ```./build/Beam``` to run the app.

If your are working on OS X or linux, you can run ```./scripts/dependencies.sh```. This would automatically download and install all
the dependencies for you (if they weren't already installed).

To run tests: ```./scripts/test.sh```

**All scripts should be run from the project root directory**.

## License

```
   Copyright 2017 Oluwatobi Adeyinka

   
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
```
