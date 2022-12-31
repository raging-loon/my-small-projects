cmake_minimum_required(VERSION 3.7)

project(echosrv VERSION 1.0)

add_executable(echosrv
  ./src/main.cpp
  ./src/echosrv.cpp
  ./src/mthreads.cpp
)

target_include_directories(echosrv PUBLIC "./include")

