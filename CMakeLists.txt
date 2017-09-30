cmake_minimum_required(VERSION 3.8)
project(Beam)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/osx_cocoa-unicode-3.0 -I/Users/tobi/Documents/programming/projects/Beam/lib/wxWidgets/include -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__  -stdlib=libc++ -std=c++11")
set(CMAKE_SHARED_LINKER_FLAGS "-L${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau-3.0")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/wxWidgets/build-debug/lib/wx/include/osx_cocoa-unicode-3.0)

find_package(wxWidgets COMPONENTS adv core base REQUIRED)
include(${wxWidgets_USE_FILE})

set(HEADER_FILES src/main.h src/ui/mainframe.h)
set(SOURCE_FILES src/main.cpp src/ui/mainframe.cpp)

add_executable(Beam ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(Beam ${wxWidgets_LIBRARIES})
