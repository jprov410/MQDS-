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
