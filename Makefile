all:
	gcc -c main.c
	gcc -c mementry.c
	ar rc libmym.a mementry.o
	gcc -o mym main.c libmym.a

clean:
	rm -rf *.o
	rm -rf libmym.a
	
