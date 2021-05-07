# Unit 3 examples

This folder contains the examples seen in the lecture "Unit 3 - Multicore, TLP 
and OpenMP". I highly recommend to compile, run and mofify the files in order to
practice, learn and test the concepts seen in the lecture. This is the 
structure of the directory:

        ├── bonus.c                 inner/outter loop thread creation example
        ├── datascope               OpenMP data scope
        │   ├── default_none.c      default(none)
        │   ├── firstprivate.c      firsprivate(x)
        │   ├── Makefile            
        │   ├── private.c           private(x)
        │   └── shared.c            shared(x)
        ├── helloworld              Basic examples
        │   ├── hello_world.c       Print a Hello world per thread
        │   ├── library.c           Call some OpenMP libraries from "omp.h"
        │   ├── Makefile
        │   └── num_threads.c       Different numbers of threads
        ├── Makefile
        ├── README.md               This file
        └── worksharing             Share work between loops
            ├── for_loop.c          For loop example
            └── Makefile

There are several Makefiles in each directory. To compile them use the Makefile 
running ("$" indicates that we are in a shell):

    $ make

And to clean the binary generated call the target "clean" by doing:

    $ make clean
    
In the case of the worksharing/for_loop.c:

    $ make
    gcc for_loop.c -o for_loop -fopenmp

And to clean it:

    $ make clean
    rm for_loop

The Makefiles "helloworld/Makefile" and "datascope/Makefile" are more advanced 
and are able to compile several files at the same time. The code is commented 
and you can test it and modify it to learn about Makefiles. The compilation is 
done in the same way. Just run "make":

    $ make
    gcc library.c -o library -fopenmp
    gcc hello_world.c -o hello_world -fopenmp
    gcc num_threads.c -o num_threads -fopenmp

And the same to remove the binaries generated:

    $ make clean
    rm library hello_world num_threads

