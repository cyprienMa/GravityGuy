cmake_minimum_required(VERSION 3.4)
project(GravityGuy)
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)
add_executable(main main.cpp)
