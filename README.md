# ![](http://i.imgur.com/r305Fz0.png) FreeMalloc
A smarter free() and malloc() function for C. Uses an array of size 5000 (can be changed easily) to allocate memory.

+ free() will run a couple of checks to see if the memory has been allocated in the array already before it tries to free the memory up.
+ malloc() will try to allocate space inside the array with the given size.

Program will also try to prevent fragmentation issues by merging open blocks of memory in the array.

## ![](http://i.imgur.com/yUTUt5e.png) Usage
Modify the `main.c` file to suit your needs. Then do the following commands to run your program:

    In terminal type: make && make clean
    (make clean is optional)
    
    ./mym
    The program name can be changed in the Makefile file.
