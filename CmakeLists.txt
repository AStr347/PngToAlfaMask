cmake_minimum_required(VERSION 3.5) # check CMake version.


project(PngToAlfaMask)# Название проекта
set(CMAKE_CXX_STANDARD 17)# use c++17

#set Release/Debug dir place
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/runtime)
#all our files in src
set(SOURCEDIR ${PROJECT_SOURCE_DIR}/src)


# Find SFML shared libraries
if (WIN32)
	# values for find boost in windows
	# set your paths
	set(SFML_DIR C:/SDK/SFML-2.5.1/lib/cmake/SFML)
	set(SFML_INCLUDE_DIR C:/SDK/SFML-2.5.1/include)
endif()

find_package(SFML 2.5
		COMPONENTS
		system window graphics REQUIRED
)
set(SFML_LIBS sfml-graphics sfml-window sfml-system)


# Find Boost shared libraries
if (WIN32)
	# values for find boost in windows
	# set your paths
	set(Boost_USE_STATIC_LIBS 		ON)  # only find static libs
	set(Boost_USE_DEBUG_LIBS 		ON)  # ignore debug libs and
	set(Boost_USE_RELEASE_LIBS 		ON)  # only find release libs
	set(Boost_USE_MULTITHREADED 	ON)
	set(Boost_USE_STATIC_RUNTIME    OFF)
	set(BOOST_INCLUDEDIR C:/SDK/boost_1_76_0/)
	set(BOOST_LIBRARYDIR C:/SDK/boost_1_76_0/stage/lib)
	set(BOOST_ROOT C:/SDK/boost_1_76_0/boost)
endif()

find_package(Boost
		COMPONENTS
		filesystem REQUIRED
)



include_directories(${SOURCEDIR}/include ${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})# set dirs with headers

add_executable(PngToAlfaMask ${SOURCEDIR}/Main.cpp)

# Add sub projects
add_subdirectory(${SOURCEDIR}/Convert)
add_subdirectory(${SOURCEDIR}/StringHelp)
add_subdirectory(${SOURCEDIR}/Pat)
add_subdirectory(${SOURCEDIR}/CompressedMem)
add_subdirectory(${SOURCEDIR}/MyImage)
add_subdirectory(${SOURCEDIR}/Amask)

#lin our libs
target_link_libraries(PngToAlfaMask Pat MyImage Amask)
