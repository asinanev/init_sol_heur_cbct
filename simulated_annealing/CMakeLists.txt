target_sources(cbct
        PRIVATE simulated_annealing.cpp
        PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES simulated_annealing.h)