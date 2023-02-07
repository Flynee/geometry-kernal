cmake_minimum_required(VERSION 3.2)
project(GEOMETRY-KERNAL)

set(ROOT ${PROJECT_SOURCE_DIR})
# mode
set(CMAKE_BUILD_TYPE Debug)



# include
include_directories("${ROOT}/include" "${ROOT}/3rd-party/include/occ")
# lib
file (GLOB ALL_LIB_SOURCES "${ROOT}/3rd-party/lib/occ/*.lib" )
link_libraries(${ALL_LIB_SOURCES})

#executable
file (GLOB ALL_SOURCES 
    "${ROOT}/src/*.cpp" "${ROOT}/src/*.c" "${ROOT}/src/*.cxx"
    "${ROOT}/src/prim/*.cpp" "${ROOT}/src/prim/*.c" "${ROOT}/src/prim/*.cxx")
set(ALL_SRCS ${ALL_SOURCES})
add_executable(main ${ALL_SRCS})