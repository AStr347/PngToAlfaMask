add_library(MyImage STATIC MyImage.cpp)# Create static lib
target_include_directories(MyImage PUBLIC include)
set(MYIMAGE_RELEASE_LIBS Pat Convert StringHelp CompressedMem ${SFML_LIBS})
target_link_libraries(MyImage PRIVATE ${MYIMAGE_RELEASE_LIBS})
