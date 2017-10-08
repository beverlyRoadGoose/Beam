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

cmake_minimum_required(VERSION 3.2)
project(Beam)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if (APPLE)
    set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/osx_cocoa-unicode-3.0 -I/${PROJECT_SOURCE_DIR}/lib/wxWidgets/include -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__  -stdlib=libc++ -std=c++11")
    set(CMAKE_SHARED_LINKER_FLAGS "-L${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau-3.0")
elseif (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-I/${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/gtk3-unicode-3.0 -I/${PROJECT_SOURCE_DIR}/lib/wxWidgets/include -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread")
    set(CMAKE_SHARED_LINKER_FLAGS "-L/${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib -pthread   -Wl,-rpath,/${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib -lwx_gtk3u-3.0")
endif ()

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/curlpp/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/include)

if (APPLE)
    include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/osx_cocoa-unicode-3.0)
elseif (UNIX AND NOT APPLE)
    include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/gtk3-unicode-3.0)
endif ()

find_package(wxWidgets COMPONENTS adv core base REQUIRED)
include(${wxWidgets_USE_FILE})

#sqlite libraries
link_directories(${PROJECT_SOURCE_DIR}/lib/sqlite/build-debug/.libs)

find_package(CURL REQUIRED)

#curlpp libraries
link_directories(${PROJECT_SOURCE_DIR}/lib/curlpp)

# create persistence dir during build
add_custom_target(build-time-make-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/build/persistence)

add_library(beam-database
    src/database/databasemanager.h
    src/database/databasemanager.cpp
    src/database/repositories/podcasts_repository.h
    src/database/repositories/podcasts_repository.cpp
    src/database/repositories/episodes_repository.h
    src/database/repositories/episodes_repository.cpp)
target_link_libraries(beam-database sqlite3)

add_library(beam-entities
    src/entities/podcast.h
    src/entities/podcast.cpp
    src/entities/episode.h
    src/entities/episode.cpp)

add_library(beam-networking
    src/networking/network_utils.cpp
    src/networking/network_utils.h)
target_link_libraries(beam-networking curlpp ${CURL_LIBRARIES})

add_library(beam-ui
    src/ui/mainframe.h
    src/ui/mainframe.cpp
    src/ui/panels/podcasts_panel.cpp
    src/ui/panels/podcasts_panel.h
    src/ui/widgets/podcasts_list_item_panel.cpp
    src/ui/widgets/podcasts_list_item_panel.h
    src/ui/widgets/podcasts_list_panel.cpp
    src/ui/widgets/podcasts_list_panel.h)
target_link_libraries(beam-ui ${wxWidgets_LIBRARIES})

add_executable(Beam src/main.h src/main.cpp)
target_link_libraries(Beam beam-database beam-entities beam-ui beam-networking)

#####################
# Testing
#####################

enable_testing()
add_library(Catch lib/catch/catch.hpp lib/catch/catch.cpp)

add_library(TestUtils tests/testutils.h tests/testutils.cpp)
target_link_libraries(TestUtils beam-database)

add_executable(podcast-tests tests/entities/podcasttests.cpp)
target_link_libraries(podcast-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME PodcastTests COMMAND podcast-tests)

add_executable(episode-tests tests/entities/episodetests.cpp)
target_link_libraries(episode-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME EpisodeTests COMMAND episode-tests)

add_executable(database-manager-tests tests/database/databasemanagertests.cpp)
target_link_libraries(database-manager-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME DatabaseManagerTests COMMAND database-manager-tests)

add_executable(podcasts-repository-tests tests/database/repositories/podcasts_repository_tests.cpp)
target_link_libraries(podcasts-repository-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME PodcastsRepositoryTests COMMAND podcasts-repository-tests)

add_executable(episodes-repository-tests tests/database/repositories/episodes_repository_tests.cpp)
target_link_libraries(episodes-repository-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME EpisodesRepositoryTests COMMAND episodes-repository-tests)

add_executable(network-utils-tests tests/networking/network_utils_tests.cpp)
target_link_libraries(network-utils-tests Catch beam-networking)
add_test(NAME NetworkUtilsTests COMMAND network-utils-tests)