proj06: proj06.student.o
	g++ -pthread -o proj06 proj06.student.o

proj06.student.o: proj06.student.c
	g++ -c proj06.student.c
