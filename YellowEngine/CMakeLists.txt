cmake_minimum_required(VERSION 3.13)

file(GLOB src "*.cpp" "*.h")

add_subdirectory(ext)

add_library(YellowEngine ${src})
target_link_libraries(YellowEngine PUBLIC GLAD Opengl32)
target_include_directories(YellowEngine PUBLIC .)
