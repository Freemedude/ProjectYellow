cmake_minimum_required(VERSION 3.15)

# Glad
add_library(glad glad/glad.c glad/glad.h KHR/khrplatform.h)
target_include_directories(glad PUBLIC .)