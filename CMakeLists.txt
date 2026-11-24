cmake_minimum_required(VERSION 3.26)

project(PngToAlfaMask)
set(CMAKE_CXX_STANDARD 17)
include(libbuilder.cmake)

# set Release/Debug dir place
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")
# all our files in src
set(SOURCEDIR ${PROJECT_SOURCE_DIR}/src)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions("__DEBUG")
endif()

# Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML
			 COMPONENTS
			 system window graphics REQUIRED
)
set(SFML_DEBUG_LIBS sfml-graphics sfml-window sfml-system)
set(SFML_RELEASE_LIBS sfml-graphics sfml-window sfml-system)

# Find Boost
set(Boost_USE_STATIC_LIBS 		ON)
set(Boost_USE_DEBUG_LIBS 		ON)
set(Boost_USE_RELEASE_LIBS 		ON)
set(Boost_USE_MULTITHREADED 	ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(Boost_NO_WARN_NEW_VERSIONS  ON)
set(Boost_ARCHITECTURE "-x64")
find_package(Boost
			 COMPONENTS 
			 system filesystem program_options REQUIRED)
set(BOOST_DEBUG_LIBS ${Boost_FILESYSTEM_LIBRARY_DEBUG} ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG})
set(BOOST_RELEASE_LIBS ${Boost_FILESYSTEM_LIBRARY_RELEASE} ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE})

# set dirs with headers
include_directories(${SOURCEDIR}/include ${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

# Find our static lib
add_subdirectory(${SOURCEDIR}/compressor)

# Link Project
add_executable(${PROJECT_NAME} ${SOURCEDIR}/main.cpp)
target_link_libraries(${PROJECT_NAME}
	PRIVATE optimized ${BOOST_RELEASE_LIBS} ${SFML_RELEASE_LIBS} compressor
	PRIVATE debug ${BOOST_DEBUG_LIBS} ${SFML_DEBUG_LIBS}
)
