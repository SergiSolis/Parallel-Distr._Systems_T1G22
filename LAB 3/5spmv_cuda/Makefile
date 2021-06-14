CC=nvcc
OBJ=spmv
FLAGS= -O3
all: $(OBJ).cu
	$(CC) $(FLAGS)  -o $(OBJ).x $<
clean:
	rm $(OBJ).x
cleanall:
	rm $(OBJ).x *.err *.out
