cmake_minimum_required(VERSION 3.7)


project(options VERSION 1.0)

add_library(options SHARED
  ./src/liboptions.c
)

target_include_directories(options PUBLIC "./include")

set_target_properties(options PROPERTIES VERSION ${PROJECT_VERSION})



set_target_properties(options PROPERTIES SOVERSION 1)