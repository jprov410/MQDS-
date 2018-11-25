#add directory that with classesmake
add_subdirectory(classes)

#directories that contain source code
include_directories(${MQDS_SOURCE_DIR}/MQDS/src/classes)
#headers
include_directories(${MQDS_SOURCE_DIR}/MQDS/include)

#directories that conatin compiled libraries
include_directories(${MQDS_BINARY_DIR}/MQDS/src/classes)

#define the MQDS libraries
set(MQDS_LIBRARIES
        CLASSES)

add_executable(mqds.exe main.cpp)

if(MPI_CXX_FOUND)
    target_link_libraries(mqds.exe
            ${MQDS_LIBRARIES}
            MPI::MPI_CXX
            ${LAPACK_LIBRARIES}
            ${BLAS_LIBRARIES})
else()
    message(ERROR "Must have MPI installed for proper compilation")
endif()

target_include_directories(mqds.exe PRIVATE ${CMAKE_SOURCE_DIR})
