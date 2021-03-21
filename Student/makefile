main : main.o dlist.o comm.o menu.o student.o
	gcc main.o dlist.o comm.o menu.o student.o -Wall -o main
	rm *.o -rf

comm.o : comm.h comm.c
	gcc -c -Wall comm.c 

dlist.o : dlist.h dlist.c
	gcc -c -Wall dlist.c

student.o : student.h student.c
	gcc -c -Wall student.c

menu.o : menu.h menu.c
	gcc -c -Wall menu.c

main.o : comm.h main.c
	gcc -c -Wall main.c

