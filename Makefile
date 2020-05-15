LIBPATH= SFML-2.5.1/lib/
SOURCEPATH= PngToAlfaMask
INCLUDEPATH= -I SFML-2.5.1/include/SFML/ -I SFML-2.5.1/include/SFML/Graphics/ -I SFML-2.5.1/include/ -I $(LIBPATH)
LIBS= -Lsfml-graphics.lib -Lsfml-window.lib -Lsfml-system.lib
EXEPATH= x64/Release
DEFINES= -D SFML_STATIC
PREFIX= g++ $(DEFINES) $(INCLUDEPATH) 

all: main

Paths:
	$(PREFIX) -c $(SOURCEPATH)/Paths.cpp -o obj/Paths.o -std=c++11
	
Amask:
	$(PREFIX) -c $(LIBS) $(SOURCEPATH)/Amask.cpp -o obj/Amask.o -std=c++11
	
MyImage: Paths
	$(PREFIX) -c obj/Paths.o  $(LIBS) $(SOURCEPATH)/MyImage.cpp -o obj/MyImage.o -std=c++11

PngToAlfaMask: Paths Amask MyImage
	$(PREFIX) -o $(EXEPATH)/PngToAlfa.exe obj/Paths.o obj/Amask.o obj/MyImage.o $(SOURCEPATH)/PngToAlfaMask.cpp  -std=c++11 $(LIBS)

main: PngToAlfaMask
