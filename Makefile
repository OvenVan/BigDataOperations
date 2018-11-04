#MakeFile created by automake-OvenVan

BIN	= a.exe
CC	= gcc
CFLAG	= -g3 -Wall -static-libgcc =std=c++11
CXX	= g++
CXXFLAG	= -g3 -Wall -static-libgcc -std=c++11 -lstdc++
OBJ	= big_int.o bigdata.o list_node.o 

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN)
	@echo "Type ./$(BIN) to start the program."

big_int.o: big_int.cpp
	$(CC) -c big_int.cpp -o big_int.o $(CXXFLAG)

bigdata.o: bigdata.cpp
	$(CC) -c bigdata.cpp -o bigdata.o $(CXXFLAG)

list_node.o: list_node.cpp
	$(CC) -c list_node.cpp -o list_node.o $(CXXFLAG)

clean:
	@rm $(BIN) *.o -f *.log
	@echo "Remove Successful."
