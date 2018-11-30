set(MQDS_HEADER_FILES
        universe.h
        io.h
        system.h
        bath.h
        units.h
        constants.h
        random.h
        )

# Install the headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h","*.hpp")