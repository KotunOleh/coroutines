cmake_minimum_required(VERSION 3.15)
project(coroutines VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(coroutines
	main.cpp
	routine.cpp
)

target_include_directories(coroutines PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

