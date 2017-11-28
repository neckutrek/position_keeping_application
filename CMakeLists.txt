cmake_minimum_required(VERSION 3.0)
project(aspka)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3")

include_directories("include")

add_executable(${PROJECT_NAME} 
   src/main.cpp
   src/application.cpp
   src/model.cpp
   src/view.cpp
   src/controller.cpp)
#   src/market_simulator.cpp)