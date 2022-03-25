add_library(CompressedMem STATIC CompressedMem.cpp)# Create static lib
target_include_directories(CompressedMem PUBLIC include)
target_link_libraries(CompressedMem Convert)