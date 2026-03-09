cmake_minimum_required(VERSION 3.20)
project(FunctionNamesPass)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

#you add pass here and create module

add_library(pass MODULE pass.cpp)

#here you linke library

target_link_libraries(pass LLVM)

#setting up properties
set_target_properties(pass PROPERTIES
    CXX_STANDARD 17
    PREFIX ""        
)