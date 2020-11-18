SRC = bmp2txt.cpp 
OBJ = $(SRC:.cpp=.o)
g = g++

b2t : $(OBJ) 
	$(g) -o b2t $(OBJ)
bmp2txt.o : bmp2txt.cpp bmp.h
	$(g) -c bmp2txt.cpp
clean :
	rm -rf b2t $(OBJ) 
