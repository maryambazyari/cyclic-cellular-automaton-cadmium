cmake_minimum_required(VERSION 3.16)
project(cyclic_ca)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main_cyclic main_cyclic.cpp)

set(CADMIUM_V2_DIR "" CACHE PATH "Path to Cadmium v2 include directory")
set(JSON_DIR "${CMAKE_SOURCE_DIR}/external" CACHE PATH "Path to nlohmann/json include directory")
set(BOOST_DIR "" CACHE PATH "Path to Boost include directory")

if(NOT CADMIUM_V2_DIR)
    message(FATAL_ERROR "Please set CADMIUM_V2_DIR to the Cadmium v2 include folder")
endif()

if(NOT BOOST_DIR)
    message(FATAL_ERROR "Please set BOOST_DIR to the Boost include folder")
endif()

target_include_directories(main_cyclic PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CADMIUM_V2_DIR}
    ${JSON_DIR}
    ${BOOST_DIR}
)

if(MSVC)
    target_compile_options(main_cyclic PUBLIC /std:c++17)
else()
    target_compile_options(main_cyclic PUBLIC -std=c++17)
endif()