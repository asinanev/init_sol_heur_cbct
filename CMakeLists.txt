cmake_minimum_required(VERSION 3.29)
project(curriculum_based_course_timetabling)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(cbct SHARED
        random_sampling/random_sampling.h
        hill_climbing/hill_climbing.h
        simulated_annealing/simulated_annealing.h
        plant_prop/plant_prop.h)
target_include_directories(cbct PRIVATE "${PROJECT_SOURCE_DIR}")
add_subdirectory("validator")
add_subdirectory("random_sampling")
add_subdirectory("hill_climbing")
add_subdirectory("simulated_annealing")
add_subdirectory("plant_prop")


add_executable(app
        app.cpp)
target_sources(app PRIVATE "app.cpp")
target_link_libraries(app PRIVATE cbct)

install(TARGETS cbct FILE_SET HEADERS)