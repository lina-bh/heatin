cmake_minimum_required(VERSION 3.10)

project(heatin)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

find_package(Qt5 COMPONENTS Widgets REQUIRED) # Charts

add_subdirectory(extern/libsensors-cpp)
set_target_properties(sensortest PROPERTIES EXCLUDE_FROM_ALL 1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_CLANG_TIDY 
        clang-tidy;
        -checks=*,-fuchsia-default-arguments-*,-modernize-use-trailing-return-type,-llvm-header-guard,-readability-named-parameter,-*-namespace-comment*,-*-uppercase-literal-suffix,-cppcoreguidelines-owning-memory,-readability-static-accessed-through-instance,cppcoreguidelines-special-member-functions,-abseil-*;
        -header-filter=*.hpp;)

    # set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE 
    #     include-what-you-use;
    #     -Xiwyu --no_comments)

    set(CMAKE_CXX_CPPCHECK
        cppcheck;
        --std=c++17;
        --enable=warning,style,performance;
        --inconclusive;
        --platform=unix64;
        --inline-suppr;
        --suppress=preprocessorErrorDirective)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

add_executable(heatin
    src/CPU.cpp
    src/main.cpp
    src/MainWindow.cpp
    src/PCI.cpp
    src/SensorsController.cpp
    src/SensorsUtil.cpp
    src/Subfeature.cpp
    src/Frequency.cpp
    src/SysfsFile.cpp
)
target_link_libraries(heatin PRIVATE pci Qt5::Widgets sensors sensors-c++)
