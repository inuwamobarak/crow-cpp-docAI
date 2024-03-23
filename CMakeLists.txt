cmake_minimum_required(VERSION 3.0)
project(my_crow_app)

add_executable(my_crow_app main.cpp)
target_link_libraries(my_crow_app pthread)
