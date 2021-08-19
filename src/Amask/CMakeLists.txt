add_library(Amask STATIC Amask.cpp)# Create static lib
set(AMASK_RELEASE_LIBS Pat Convert StringHelp ${SFML_LIBS})
target_link_libraries(Amask PRIVATE ${AMASK_RELEASE_LIBS})
