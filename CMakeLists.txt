cmake_minimum_required(VERSION 3.16)

project(particle-garden LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/SDL)

add_executable(particle-garden
  src/main.cc
  src/particle.cc
  src/particle.h
)

target_link_libraries(particle-garden PRIVATE SDL3::SDL3)