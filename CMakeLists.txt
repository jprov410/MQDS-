cmake_minimum_required(VERSION 3.10)
project(MQDS
        LANGUAGES CXX
        )

set(MQDS_VERSION_MAJOR 0)
set(MQDS_VERSION_MINOR 0)
set(MQDS_VERSION_PATCH 1)

set(MQDS_VERSION "${MQDS_VERSION_MAJOR}.${MQDS_VERSION_MINOR}.${MQDS_VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER mpicxx)


include(GNUInstallDirs)

find_package(LAPACK)
find_package(MPI)

if(MPI_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS} ")
endif()


add_subdirectory(MQDS)

#CMAKE configuration
include(CMakePackageConfigHelpers)
configure_package_config_file(
        mqdsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/mqdsConfig.cmake
        INSTALL_DESTINATION share/cmake/MQDS
        )
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/mqdsConfigVersion.cmake
        VERSION ${MQDS_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mqdsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/mqdsConfigVersion.cmake
        DESTINATION share/cmake/mqds
)

install(EXPORT MQDSTargets
        NAMESPACE MQDS::
        DESTINATION share/cmake/mqds
        )
