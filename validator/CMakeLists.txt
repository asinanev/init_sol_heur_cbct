target_sources(cbct
        PRIVATE validator.cpp
        PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES validator.h)