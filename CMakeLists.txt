cmake_minimum_required(VERSION 3.10)
project(MQDS
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER mpicxx)

find_package(LAPACK)
find_package(MPI)

if(MPI_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS} ")
endif()


add_subdirectory(MQDS)

