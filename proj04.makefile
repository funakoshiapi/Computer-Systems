proj04: proj04.student.o
	g++ -o proj04 proj04.student.o

proj04.student.o: proj04.student.c
	g++ -c proj04.student.c