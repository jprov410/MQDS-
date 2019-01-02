set(MQDS_HEADER_FILES
        universe.h
        io.h
        units.h
        constants.h
        random.h
        system.h
        systemfactory.h
        electronicsite.h
        bath.h
        bathfactory.h
        harmonic.h
        method.h
        methodfactory.h
        pldm.h
        calculation.h
        calculationfactory.h
        redmat.h
        )

# Install the headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h","*.hpp")