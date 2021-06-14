CC=nvc
OBJ=axpy
FLAGS= -acc -O3 -Minfo=all -ta=tesla:cc50 
all: $(OBJ).c
	$(CC) $(FLAGS)  -o $(OBJ).x $<
clean:
	rm $(OBJ).x
cleanall:
	rm $(OBJ).x *.err *.out
