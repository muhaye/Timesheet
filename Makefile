CFLAGS = -Wall -pedantic -std=c99
# LFLAGS = -lm 
CC = gcc

output: print_table.o last_day.o main.o 
	$(CC) $(CFLAGS)  print_table.o last_day.o main.o -o output && ./output 1 20

main.o: main.c
	$(CC) -c main.c

print_table.o: print_table.c print_table.h
	$(CC) -c print_table.c 
	
clean:
	rm -f *.o output
last_day.o: last_day.c last_day.h
	$(CC) -c last_day.c 
	
clean:
	rm -f *.o output
