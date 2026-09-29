cmake_minimum_required(VERSION 4.3)

project(LiturgyMake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LiturgyMake
        main.cpp
        cli/CLI.cpp
        cli/CLI.h
        project/Project.cpp
        project/Project.h
        build/Builder.cpp
        build/Builder.h
)