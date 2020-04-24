cmake_minimum_required(VERSION 3.3)

file(GLOB src "*.cpp" "*.h")

message (${src})
add_library(YellowEngine ${src})
add_subdirectory(ext)
target_link_libraries(YellowEngine GLAD Opengl32)
target_include_directories(YellowEngine PUBLIC .)