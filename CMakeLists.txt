cmake_minimum_required(VERSION 3.6)
project(MogicTower)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -pthread")
#set(CMAKE_BUILD_TYPE Profile)
#set(CMAKE_CXX_FLAGS_PROFILE "-pg")

set(SOURCE_FILES
        damage.cpp
        damage.h
        debug.cpp
        debug.h
        eval.cpp
        eval.h
        graph.cpp
        graph.h
        helpers.h
        main.cpp
        mogic.h
        mogicTower.cpp
        mogicTower.h
        route.cpp
        route.h
        search.cpp
        search.h
        AI.h
        AI.cpp
        )


add_executable(MogicTower ${SOURCE_FILES})