cmake_minimum_required(VERSION 3.7)

project(portscanner VERSION 0.1)


add_executable(portscanner
  ./src/main.cpp
  ./src/nxs_options.cpp
)
# add_subdirectory(portscanner ./liboptions)

target_include_directories(portscanner PUBLIC "./include" "liboptions/include")

add_library(liboptions SHARED IMPORTED)

set_target_properties(liboptions PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/liboptions/liboptions.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/liboptions/include"
)



target_link_libraries(portscanner pthread liboptions)

