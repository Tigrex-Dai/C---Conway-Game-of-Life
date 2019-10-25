all = main.c grille.c io.c jeu.c grille.h io.h jeu.h
obj = grille.o io.o main.o jeu.o
cc = gcc
cflag = -Wall

main : $(obj)
	$(cc) $(cflag) $(obj) -o main
	
main.o : main.c grille.h io.h jeu.h 
	$(cc) $(cflag) -c main.c 
	
grille.o : grille.c grille.h 
	$(cc) $(cflag) -c grille.c 
	
io.o : io.c io.h grille.h jeu.h
	$(cc) $(cflag) -c io.c 

jeu.o : jeu.c jeu.h grille.h
	$(cc) $(cflag) -c jeu.c 
	
clean:
	rm *.o main

dist:
	tar -c doc/ grilles/ $(all) doxyfile Makefile -f daiyuquan-GoL-ver2.4.tar.xz -z
