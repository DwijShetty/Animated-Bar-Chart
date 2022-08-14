cmake_minimum_required(VERSION 3.20)
project(AnimatedBarChart)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AnimatedBarChart
        application.cpp
        bar.h
        barchart.h
        barchartanimate.h
        myrandom.h)
add_executable(Tests
        tests.cpp
        bar.h
        barchart.h
        barchartanimate.h
        myrandom.h)
