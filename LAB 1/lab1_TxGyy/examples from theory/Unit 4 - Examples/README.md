# Unit 4 examples

This folder contains the examples seen in the lecture "Unit 4 - OpenMP II". I 
highly recommend to compile, run and mofify the files in order to practice, 
learn and test the concepts seen in the lecture. This is the structure of the directory:

        ├── README.md               This file
        ├── reduction               
        │   ├── addition.c          reduction(+:)
        │   └── Makefile
        ├── schedule
        │   ├── Makefile
        │   └── schedulers.c        5 schedulers performance
        ├── simd
        │   ├── arrays.c            simd
        │   ├── Makefile
        │   └── reduction.c         simd reduction()
        ├── synchronization
        │   ├── atomic.c            atomic synchronization
        │   ├── barrier.c           barrier synchronization
        │   ├── critical.c          critical synchronization
        │   └── Makefile
        └── tasks
            ├── Makefile
            ├── tasks.c             Task definition
            └── taskwait.c          Task definition with taskwait



There are several Makefiles in each directory. To compile them use the Makefile 
running ("$" indicates that we are in a shell):

    $ make

And to clean the binary generated call the target "clean" by doing:

    $ make clean
    
In the case of the reduction/addition.c:

    $ make
    gcc addition.c -o addition -fopenmp

And to clean it:

    $ make clean
    rm addition

