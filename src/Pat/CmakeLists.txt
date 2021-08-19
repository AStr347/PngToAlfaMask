
add_library(Pat STATIC Pat.cpp)# Create static lib
target_link_libraries(  Pat 
                        PRIVATE 
                        debug ${Boost_FILESYSTEM_LIBRARY_DEBUG} StringHelp 
                        PRIVATE
                        optimized ${Boost_FILESYSTEM_LIBRARY_RELEASE} StringHelp)