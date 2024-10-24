target_sources(cbct
        PRIVATE random_sampling.cpp
        PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES random_sampling.h)