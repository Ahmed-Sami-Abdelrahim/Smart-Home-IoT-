cmake_minimum_required(VERSION 3.17)

# Project name and version
project(device-controller VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files
set(SOURCE_FILES
    src/clientHandler/clientHandler.cpp
    src/deviceManager/deviceManager.cpp
    src/parser/parser.cpp
    src/serviceManager/serviceManager.cpp
    src/deviceManager/Led.cpp
    src/clientHandler/HttpGetClient.cpp
    src/deviceManager/AirConditioner.cpp
    main.cpp
)

# Define include directories
include_directories(
    src/clientHandler
    src/deviceManager
    src/parser
    src
    src/serviceManager
)

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Define installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Optionally, add target-specific compiler options or warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)


