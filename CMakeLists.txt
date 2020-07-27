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

find_package(Qt5 COMPONENTS Widgets REQUIRED) # Charts

add_subdirectory(extern/libsensors-cpp)
set_target_properties(sensortest PROPERTIES EXCLUDE_FROM_ALL 1)

set(CMAKE_CXX_CLANG_TIDY 
    clang-tidy;
    -checks=*,-fuchsia-default-arguments-*,-modernize-use-trailing-return-type,-llvm-header-guard,-readability-named-parameter,-*-special-member-functions,-*-namespace-comment*,-*-uppercase-literal-suffix,-cppcoreguidelines-owning-memory;
    -header-filter=src/*.hpp;)

# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE 
#     include-what-you-use;
#     -Xiwyu --no_comments;
#     -Xiwyu --quoted_includes_first;
#     -Xiwyu --no_fwd_decls)

set(CMAKE_CXX_CPPCHECK
    cppcheck;
    --std=c++17)

add_executable(heatin
    src/CPU.c
    src/main.cpp
    src/MainWindow.cpp
    src/Measurement.cpp
    src/PCI.cpp
    src/SensorsController.cpp
    src/SensorsUtil.cpp
)
target_link_libraries(heatin PRIVATE pci Qt5::Widgets sensors sensors-c++)
