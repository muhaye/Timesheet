CFLAGS = -Wall -v -pedantic -std=c99 -L/usr/local/lib/ -lhpdf
# LFLAGS = -lm 
CC = gcc

output: pdf_printer.o print_table.o last_day.o main.o 
	$(CC) $(CFLAGS) pdf_printer.o print_table.o last_day.o main.o -o output && ./output 1 20

main.o: main.c
	$(CC) -c main.c

pdf_printer.o: pdf_printer.c pdf_printer.h
	$(CC) -c -I/Users/muhaye/Py/Timesheet/libharu/include -Ilibharu/include pdf_printer.c 

print_table.o: print_table.c print_table.h
	$(CC) -c print_table.c 
	
clean:
	rm -f *.o output
last_day.o: last_day.c last_day.h
	$(CC) -c last_day.c 
	
clean:
	rm -rf *.o output
