OBJ=list_node.o big_int.o bigdata.o
EXE=a.exe

$(EXE):$(OBJ)
	g++ $(OBJ) -o $(EXE)
	@echo "Type ./$(EXE) to start the program."

bigdata.o:bigdata.cpp list_node.h big_int.h
	gcc -c bigdata.cpp

big_int.o:big_int.cpp list_node.h big_int.h
	gcc -c big_int.cpp

list_node.o:list_node.cpp list_node.h
	gcc -c list_node.cpp


clean:
	@rm $(EXE) *.o -f *.log
	@ls -ll
