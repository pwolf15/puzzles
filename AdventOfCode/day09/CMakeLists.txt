cmake_minimum_required(VERSION 3.16)

project(day09)

add_compile_options(--std=gnu++2a)

find_package(Boost 1.50)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(main main.cpp)
endif()