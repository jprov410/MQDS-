set(MQDS_HEADER_FILES
        universe.h
        input.h
        output.h
        system.h
        bath.h
        units.h
        constants.h
        random.h
        )

add_library(HEADERS
        ${MQDS_HEADER_FILES}
        )