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

cmake_minimum_required(VERSION 3.8)
project(Beam)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/osx_cocoa-unicode-3.0 -I/Users/tobi/Documents/programming/projects/Beam/lib/wxWidgets/include -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__  -stdlib=libc++ -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-L${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau-3.0")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/osx_cocoa-unicode-3.0)

find_package(wxWidgets COMPONENTS adv core base REQUIRED)
include(${wxWidgets_USE_FILE})

#sqlite libraries
link_directories(${PROJECT_SOURCE_DIR}/lib/sqlite/build-debug/libs)

set(HEADER_FILES
    src/main.h
    src/ui/mainframe.h
    src/entities/podcast.h
    src/entities/episode.h
    src/database/databasemanager.h)

set(SOURCE_FILES
    src/main.cpp
    src/ui/mainframe.cpp
    src/entities/podcast.cpp
    src/entities/episode.cpp
    src/database/databasemanager.cpp)

add_executable(Beam ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(Beam ${wxWidgets_LIBRARIES} sqlite3)

#####################
# Testing
#####################

enable_testing()
add_library(Catch lib/catch/catch.hpp lib/catch/catch.cpp)
add_library(TestUtils tests/testutils.h tests/testutils.cpp)

add_executable(podcast-tests tests/entities/podcasttests.cpp src/entities/podcast.h src/entities/podcast.cpp)
target_link_libraries(podcast-tests Catch TestUtils)
add_test(NAME PodcastTests COMMAND podcast-tests)

add_executable(episode-tests tests/entities/episodetests.cpp src/entities/episode.h src/entities/episode.cpp)
target_link_libraries(episode-tests Catch TestUtils)
add_test(NAME EpisodeTests COMMAND episode-tests)

add_executable(database-manager-tests tests/database/databasemanagertests.cpp src/database/databasemanager.h src/database/databasemanager.cpp)
target_link_libraries(database-manager-tests Catch TestUtils sqlite3)
add_test(NAME DatabaseManagerTests COMMAND database-manager-tests)