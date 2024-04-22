cmake_minimum_required(VERSION 3.4)
project(exo2)
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

add_executable(exo2 exo2.cpp)
target_link_libraries(exo2 Imagine::Graphics)
