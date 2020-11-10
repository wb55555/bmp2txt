SRC = bmp2txt.cpp BmpHead.cpp ColorTable.cpp Data_148.cpp Data_24.cpp
OBJ = $(SRC:.cpp=.o)
g = g++

b2t : $(OBJ) 
	$(g) -o b2t $(OBJ)
bmp2txt.o :
	$(g) -c bmp2txt.cpp
BmpHead.o :
	$(g) -c BmpHead.cpp
ColorTable.o:
	$(g) -c ColorTable.cpp
Data_148.o :
	$(g) -c Data_148.cpp
Data_24.o :
	$(g) -c Data_24.cpp
clean :
	rm -rf b2t $(OBJ) 
