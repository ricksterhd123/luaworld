cmake_minimum_required(VERSION 3.10)

project(luaworld)

add_executable(luaworld main.c)

target_link_libraries(luaworld PUBLIC lua m dl)
