proj05: proj05.student.o
	g++ -o proj05 proj05.student.o

proj05.student.o: proj05.student.c
	g++ -c proj05.student.c