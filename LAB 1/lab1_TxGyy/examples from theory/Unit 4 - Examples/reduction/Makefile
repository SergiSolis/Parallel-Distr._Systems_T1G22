CC=gcc
CFLAGS = -fopenmp

# SRC contains a list of those files ending in ".c"
SRC=$(wildcard *.c)

# The binaries that will be generated will have the same name as
# the file but the ".c" will be removed and will be stored in OBJ
OBJ=$(SRC:.c=)

# When running "make" we execute the "all" target by default
# The pre-requisites (or dependence) is to generate all the 
all: $(OBJ)

# Generate the binaries for all the *.c files
# This target is the pre-requisite of "all"
# "$<" indicates the right hand side of the target: the name of the .c file
# "$@" indicates the left hand side of the target: the name of the binary
%: %.c
	$(CC) $< -o $@ $(CFLAGS)

# Remove all the binaries generated
clean:
	rm $(OBJ)
