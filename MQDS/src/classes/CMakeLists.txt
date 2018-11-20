set(MQDS_CLASS_FILES
        universe.cpp
        input.cpp
        output.cpp
        system.cpp
        bath.cpp
        units.cpp
        constants.cpp
        random.cpp
        )

add_library(CLASSES
        ${MQDS_CLASS_FILES}
        )

#set(MQDS_INCLUDE_LIBRARY "${CMAKE_HOME_DIRECTORY}/include")
#target_include_directories(CLASSES PRIVATE ${MQDS_INCLUDE_LIBRARY})

#install(TARGETS CLASSES
#        EXPORT CLASSESTargets
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        )
