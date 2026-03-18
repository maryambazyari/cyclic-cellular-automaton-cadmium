cmake_minimum_required(VERSION 3.16)
project(cyclic_ca)

add_executable(main_cyclic main_cyclic.cpp)

set(CADMIUM_V2_DIR "C:/Users/maryam/Desktop/cadmium_v2/include")
set(JSON_DIR "C:/Users/maryam/Desktop/cadmium/json/include")
set(BOOST_DIR "C:/Users/maryam/Downloads/boost_1_90_0/boost_1_90_0")

target_include_directories(main_cyclic PUBLIC
    "."
    "include"
    ${CADMIUM_V2_DIR}
    ${JSON_DIR}
    ${BOOST_DIR}
)

if (MSVC)
    target_compile_options(main_cyclic PUBLIC /std:c++17)
else()
    target_compile_options(main_cyclic PUBLIC -std=gnu++17)
endif()