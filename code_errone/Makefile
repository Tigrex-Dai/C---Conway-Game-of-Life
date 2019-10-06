obj = alea.o io.o main.o tri.o
cc = gcc
cflag = -Wall

main : $(obj)
	$(cc) $(cflag) $(obj) -o main
	
main.o : main.c alea.h io.h tableau.h tri.h
	$(cc) $(cflag) -c main.c
	
alea.o : alea.c alea.h tableau.h
	$(cc) $(cflag) -c alea.c
	
io.o : io.c io.h tableau.h
	$(cc) $(cflag) -c io.c

tri.o : tri.c tri.h tableau.h
	$(cc) $(cflag) -c tri.c
	
clean:
	rm *.o main
