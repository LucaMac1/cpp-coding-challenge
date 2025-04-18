cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(ExampleGtest LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        bf66935e07825318ae519675d73d0f3e313b3ec6 
)
FetchContent_MakeAvailable(googletest)

find_package(SFML 2.5 REQUIRED graphics window system)

# Set the compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O0 -Wall -Wwrite-strings -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Create OBJECT_DIR variable
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/ExampleGtest.dir/src)
message("-- Object files will be output to: ${OBJECT_DIR}")

# set(SOURCES include/FizzBuzz.h src/FizzBuzz.cpp test/FizzBuzzTest.cpp)
# set(SOURCES include/RomanNumeralsConverter.h src/RomanNumeralsConverter.cpp test/RomanNumeralsConverterTest.cpp)
# set(SOURCES include/MyString.h src/MyString.cpp test/MyStringTest.cpp)
# set(SOURCES include/IPID.h include/PID.h src/PID.cpp test/PIDTest.cpp)

set(SOURCES src/main_plant_2.cpp src/InvertedPendulumSystem.cpp src/PID.cpp src/PositionSystem.cpp src/TemperatureSystem.cpp src/VelocitySystem.cpp)
set(HEADERS include/InvertedPendulumSystem.h include/PID.h include/PositionSystem.h include/TemperatureSystem.h include/VelocitySystem.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# target_link_libraries(${PROJECT_NAME} gtest_main gmock_main)

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})

find_program(GCOV_PATH gcov REQUIRED)
find_program(LCOV_PATH lcov REQUIRED)
find_program(GENHTML_PATH genhtml REQUIRED)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p gcoverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND ${GCOV_PATH} -b ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR} 
    COMMAND echo "-- Source directory: ${CMAKE_SOURCE_DIR}/src/"
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
    )

add_dependencies(gcov ${PROJECT_NAME})

add_custom_target(lcov
    COMMAND mkdir -p lcoverage
    )

add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND lcov --capture --directory ${OBJECT_DIR} --output-file lcoverage/main_coverage.info -b .
    COMMAND echo "-- Removing undesired files from main_coverage"
    COMMAND lcov --extract lcoverage/main_coverage.info '*/src/*.cpp' -o lcoverage/filtered_coverage.info
    # COMMAND lcov --remove lcoverage/main_coverage.info '*/usr/include/*' '*/gtest/*' '*/include/IFoo.h' -o lcoverage/filtered_coverage.info
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml lcoverage/filtered_coverage.info --output-directory lcoverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files. ${CMAKE_MAKE_PROGRAM} is /usr/bin/make
add_custom_target(refresh
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm CMakeCache.txt
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Testing
enable_testing()

#include headers
include_directories(include)