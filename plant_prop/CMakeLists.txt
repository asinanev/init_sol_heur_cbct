target_sources(cbct
        PRIVATE plant_prop.cpp
        PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES plant_prop.h)