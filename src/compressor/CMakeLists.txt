SLIB_INIT(
	SRCS compressor.cpp vec_1bpp.cpp vec_2bpp.cpp vec_4bpp.cpp vec_8bpp.cpp internal.cpp
	INCLUDE include
	PUB_REQ ${BOOST_RELEASE_LIBS} ${SFML_RELEASE_LIBS}
	PUB_REQ_DEBUG ${BOOST_DEBUG_LIBS} ${SFML_DEBUG_LIBS}
)