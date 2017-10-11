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

# cmake & compile configs
include(${PROJECT_SOURCE_DIR}/cmake/configs.cmake)

# include directories
include(${PROJECT_SOURCE_DIR}/cmake/includes.cmake)

# link wxWidgets libraries
find_package(wxWidgets COMPONENTS adv core base REQUIRED)
include(${wxWidgets_USE_FILE})

# link sqlite libraries
link_directories(${PROJECT_SOURCE_DIR}/lib/sqlite/build-debug/.libs)

# link curlpp libraries
find_package(CURL REQUIRED)
link_directories(${PROJECT_SOURCE_DIR}/lib/curlpp)

# link pugixml libraries
link_directories(${PROJECT_SOURCE_DIR}/lib/pugixml)

# create required dir during build
add_custom_target(build-time-make-cache-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/build/.cache)
add_custom_target(build-time-make-persistence-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/build/.persistence)

# internal app libraries
include(${PROJECT_SOURCE_DIR}/cmake/libraries.cmake)

# create app executable
add_executable(Beam src/main.h src/main.cpp)
target_link_libraries(Beam beam-database beam-entities beam-ui beam-networking)

# Testing
include(${PROJECT_SOURCE_DIR}/cmake/testing.cmake)