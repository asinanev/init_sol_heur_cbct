target_sources(cbct
        PRIVATE hill_climbing.cpp
        PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES hill_climbing.h)