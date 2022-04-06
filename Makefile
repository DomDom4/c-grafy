szukaj: main.o graph.o error.o queue.o algorithm.o
	$(CC) -o szukaj main.o graph.o error.o queue.o algorithm.o
.PHONY: clean

clean:
	-rm *.o szukaj
