include_directories(${MQDS_SOURCE_DIR}/MQDS/include)

set(MQDS_CLASS_FILES
        universe.cpp
        io.cpp
        units.cpp
        constants.cpp
        random.cpp
        system.cpp
        electronicsite.cpp
        bath.cpp
        harmonicbilinear.cpp
        method.cpp
        pldm.cpp
        calculation.cpp
        redmat.cpp
        )

add_library(CLASSES
        ${MQDS_CLASS_FILES}
        )

target_include_directories(CLASSES PRIVATE ${CMAKE_SOURCE_DIR})

# Where to install the library
install(TARGETS CLASSES
        EXPORT MQDSTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

