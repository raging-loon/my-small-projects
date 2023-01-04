cmake_minimum_required(VERSION 3.7)

project(portscanner VERSION 0.1)


add_executable(portscanner
  ./src/main.cpp
  ./src/nxs_options.cpp
)

target_include_directories(portscanner PUBLIC "./include")
