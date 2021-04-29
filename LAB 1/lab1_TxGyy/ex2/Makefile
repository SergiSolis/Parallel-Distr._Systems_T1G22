CC=gcc
CFLAGS=-fopenmp -lm -O2
OBJ=montecarlo

all:
	$(CC) $(OBJ).c -o $(OBJ) $(CFLAGS)

1:
	$(CC) $(OBJ).c -o $(OBJ) $(CFLAGS) -DNTHREADS=1

2:
	$(CC) $(OBJ).c -o $(OBJ) $(CFLAGS) -DNTHREADS=2

4:
	$(CC) $(OBJ).c -o $(OBJ) $(CFLAGS) -DNTHREADS=4

8:
	$(CC) $(OBJ).c -o $(OBJ) $(CFLAGS) -DNTHREADS=8

16:
	$(CC) $(OBJ).c -o $(OBJ) $(CFLAGS) -DNTHREADS=16

clean:
	rm $(OBJ)
