cmake_minimum_required(VERSION 3.6.2)

# Maps to a solution file (Tutorial.sln). The solution will 
# have all targets (exe, lib, dll) as projects (.vcproj)
set(PROJ_NAME client-asio)
set(EXEC_NAME Client-Boost-Asio)
set(FOLDER_PROJ_NAME ${PROJ_NAME})

project(${PROJ_NAME})

# Set INSTALL PATH as ${PROJECT_SOURCE_DIR}/install
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "Default Install Path" FORCE)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj and ALL_BUILD.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Look for PCL package
find_package(PCL 1.8 REQUIRED)
# Include directories of PCL
include_directories(${PCL_INCLUDE_DIRS})
# Link directories of PCL libraries 
link_directories(${PCL_LIBRARY_DIRS})
# Include all definitions required by PCL
add_definitions(${PCL_DEFINITIONS})

# If on Windows, make sure all symbols are exported to create a shared lib
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif()

# Check if compiler is MSVC or GNU
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # Command to output information to the console
    # Useful for displaying errors, warnings, and debugging
    message(STATUS "Setting MSVC flags")
    # Set compiler flags and options. 
    # Here it is setting the Visual Studio warning level to 4
    # Establishing default compiler as the latest version of MSVC++
    # And setting to build with multiple cores
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /MP")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # Command to output information to the console
    # Useful for displaying errors, warnings, and debugging
    message(STATUS "Setting GNU flags")

    # Set compiler flags and options.
    # Set C++11 as standard
    set (CMAKE_CXX_STANDARD 11)
    # Here it is setting to buil with multiple cores
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -j8")
endif()

# Define the folder of Includes, libraries and Runtime Files. (.h, .hpp, .ilk, .exe, .dll, .lib, .exp etc.)
set(INSTALL_INCLUDES "${CMAKE_INSTALL_PREFIX}/include")
set(INSTALL_LIBS     "${CMAKE_INSTALL_PREFIX}/lib")
set(INSTALL_BINARIES "${CMAKE_INSTALL_PREFIX}/bin")

# Add preprocessor definitions
add_definitions(-D_WIN32_WINNT=0x0A00) # Windows 10, in my case

# Assign Main as the startup project of the Solution
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXEC_NAME})

# Set of Local Variables for location
set(CBA_SRCS       "${PROJECT_SOURCE_DIR}/src")
set(CBA_INCLUDES  "${PROJECT_SOURCE_DIR}/include")

# Collect sources and headers into the variables
file(GLOB PROJECT_HEADERS_FILES 
        "${CBA_INCLUDES}/*.h"
        "${CBA_INCLUDES}/*.hpp"
        "${CBA_INCLUDES}/*.hxx")
file(GLOB PROJECT_SOURCE_FILES 
        "${CBA_SRCS}/*.c"
        "${CBA_SRCS}/*.cpp"
        "${CBA_SRCS}/*.cxx")

# Creates an executable with project files
add_executable(${EXEC_NAME} ${PROJECT_SOURCE_FILES} ${PROJECT_HEADERS_FILES})

# Linking with PCL because Boost.Asio (Temporary solution)
target_link_libraries(${EXEC_NAME} ${PCL_LIBRARIES})

# Creates a folder "cba_test" and adds target project (${PROJ_NAME}.vcproj) under it
set_property(TARGET ${EXEC_NAME} PROPERTY FOLDER "${FOLDER_PROJ_NAME}")
