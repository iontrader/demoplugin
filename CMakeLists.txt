cmake_minimum_required(VERSION 3.10)
project(st_demo_plugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_library(st_demo_plugin SHARED
        src/TradeCommenter.cpp
        src/ServerConfig.cpp
)

target_include_directories(st_demo_plugin PRIVATE
        include
        api
)

set_target_properties(st_demo_plugin PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

target_compile_options(st_demo_plugin PRIVATE
        $<$<CONFIG:Debug>:-g -O0 -fsanitize=address>
        $<$<CONFIG:Release>:-O2 -DNDEBUG>
)
