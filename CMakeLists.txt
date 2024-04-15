cmake_minimum_required(VERSION 3.21)

project(
  IRAnalysis
  VERSION 1.0
  LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(saxpy)
target_sources(saxpy PRIVATE main.cpp)

find_package(fmt REQUIRED)
target_link_libraries(saxpy fmt::fmt)

set(MODEL "SERIAL" CACHE STRING "CPU model to choose")

message(CHECK_START "Model: ${MODEL}")
if (MODEL STREQUAL "SERIAL")
  target_compile_definitions(saxpy PRIVATE USE_SERIAL)
elseif (MODEL STREQUAL "RAJA")
  find_package(RAJA REQUIRED)
  find_package(Umpire REQUIRED)

  target_link_libraries(saxpy RAJA umpire)
  target_compile_definitions(saxpy PRIVATE USE_RAJA)
elseif (MODEL STREQUAL "KOKKOS")
  find_package(Kokkos REQUIRED)
  target_link_libraries(saxpy Kokkos::kokkos)
  target_compile_definitions(saxpy PRIVATE USE_KOKKOS)
elseif (MODEL STREQUAL "OPENMP")
  target_compile_definitions(saxpy PRIVATE USE_OPENMP)
else ()
  message(FATAL_ERROR "Invalid Model: ${MODEL}")
endif ()

if (NOT MODEL STREQUAL "SERIAL")
  find_package(OpenMP REQUIRED)
  target_link_libraries(saxpy OpenMP::OpenMP_CXX)
endif ()
