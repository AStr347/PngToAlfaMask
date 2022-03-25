add_library(Amask STATIC Amask.cpp)# Create static lib
target_include_directories(Amask PUBLIC include)
set(AMASK_RELEASE_LIBS Pat Convert StringHelp ${SFML_LIBS})
target_link_libraries(Amask PRIVATE ${AMASK_RELEASE_LIBS})
