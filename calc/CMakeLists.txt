cmake_minimum_required(VERSION 3.7)

project(calc VERSION 1.0)

add_executable(calc src/calc.c)

target_include_directories(calc PUBLIC ./include)