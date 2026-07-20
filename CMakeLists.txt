cmake_minimum_required(VERSION 4.2)

project(LittleSocialNetwork LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Server)
add_subdirectory(User_app)
add_subdirectory(Utils)

