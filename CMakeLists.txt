cmake_minimum_required(VERSION 3.0)
project(aspka)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -pedantic")

include_directories("include")

add_executable(${PROJECT_NAME} 
   src/main.cpp
   src/aspka_app.cpp
   src/aspka_model.cpp
   src/aspka_view.cpp
   src/aspka_controller.cpp)