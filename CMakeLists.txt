cmake_minimum_required(VERSION 3.10)

project(heatin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
endif()

set(CMAKE_C_FLAGS_DEBUG "-Og -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -ggdb")

find_package(Qt5 COMPONENTS Widgets REQUIRED) # Charts

add_library(sensors-c++ 
    libsensors-cpp/src/sensors.cpp
    libsensors-cpp/src/error.cpp
)
include_directories(libsensors-cpp/include)

set(CMAKE_CXX_CLANG_TIDY 
    clang-tidy;
    -checks=*,-fuchsia-default-arguments-*,-modernize-use-trailing-return-type,-llvm-header-guard,-cppcoreguidelines-owning-memory,-readability-named-parameter,-*-special-member-functions,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-*-namespace-comment*,-*-uppercase-literal-suffix;
    -header-filter=src/*.hpp;)

set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE 
    include-what-you-use;
    -Xiwyu --no_comments;
    -Xiwyu --quoted_includes_first;
    -Xiwyu --no_fwd_decls)

file(GLOB SOURCES src/*.c src/*.cpp src/*.h src/*.hpp)
add_executable(heatin ${SOURCES})
target_link_libraries(heatin PRIVATE pci Qt5::Widgets sensors sensors-c++)
