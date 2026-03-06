cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME rearbox)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM CXX)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

#Add Can Library
add_subdirectory(${PROJECT_SOURCE_DIR}/Components/PUTM_EV_CAN_LIBRARY)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

file(GLOB CXX_SRC1 "${PROJECT_SOURCE_DIR}/Core/Src/*.cpp")
message(CXX_SRC1=${CXX_SRC1})

file(GLOB CXX_SRC2 "${PROJECT_SOURCE_DIR}/Tasks/Src/*.cpp")
message(CXX_SRC2=${CXX_SRC2})

file(GLOB CXX_SRC3 "${PROJECT_SOURCE_DIR}/Components/DATA/Src/*.c")
message(CXX_SRC3=${CXX_SRC3})

file(GLOB CXX_SRC4 "${PROJECT_SOURCE_DIR}/Components/AIN/Src/*.c")
message(CXX_SRC4=${CXX_SRC4})

file(GLOB CXX_SRC5 "${PROJECT_SOURCE_DIR}/Components/TCA6416A/Src/*.c")
message(CXX_SRC5=${CXX_SRC5})

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CXX_SRC1}
    ${CXX_SRC2}
    ${CXX_SRC3}
    ${CXX_SRC4}
    ${CXX_SRC5}
    # Add user sources here
)


# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/Tasks/Inc"
    "${PROJECT_SOURCE_DIR}/Components"
    "${PROJECT_SOURCE_DIR}/Components/AIN/Inc"
    "${PROJECT_SOURCE_DIR}/Components/DATA/Inc"
    "${PROJECT_SOURCE_DIR}/Components/PUTM_EV_CAN_LIBRARY/include"
    "${PROJECT_SOURCE_DIR}/Components/PUTM_EV_CAN_LIBRARY/dbc/generated"
    "${PROJECT_SOURCE_DIR}/Components/TCA6416A/Inc"
     # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    putm_ev_can

    # Add user defined libraries
)

#remove main.c from MX_Application_Src
# ist(REMOVE_ITEM MX_Application_Src "${CMAKE_SOURCE_DIR}/Core/Src/main.c")