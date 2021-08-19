add_library(MyImage STATIC MyImage.cpp)# Create static lib
set(MYIMAGE_RELEASE_LIBS Pat Convert StringHelp CompressedMem ${SFML_LIBS})
target_link_libraries(MyImage PRIVATE ${MYIMAGE_RELEASE_LIBS})
