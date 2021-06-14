CC=nvc
OBJ=cg
FLAGS= -acc -Minfo=all -ta=tesla
all: $(OBJ).c
	$(CC) $(FLAGS)  -o $(OBJ).x $<
clean:
	rm $(OBJ).x
cleanall:
	rm $(OBJ).x *.err *.out
