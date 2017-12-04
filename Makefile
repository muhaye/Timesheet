CFLAGS = -Wall -v -pedantic -std=c99 -L/usr/local/lib/ -lhpdf
# LFLAGS = -lm 
BIN = ./bin/
CC = gcc
PROG = pdf_printer.o print_table.o last_day.o main.o 

output: $(addprefix $(BIN)/, $(PROG)) 
	$(CC) $(CFLAGS) $(PROG) -o $(BIN)/output && $(BIN)/output 1 20

$(BIN)/main.o: main.c
	$(CC) -c main.c

$(BIN)/pdf_printer.o: pdf_printer.c pdf_printer.h
	$(CC) -c -I/Users/muhaye/Py/Timesheet/libharu/include -Ilibharu/include pdf_printer.c 

$(BIN)/print_table.o: print_table.c print_table.h
	$(CC) -c print_table.c 
	
$(BIN)/last_day.o: last_day.c last_day.h
	$(CC) -c last_day.c 
	
clean:
	rm -rf *.o $(BIN)/output
