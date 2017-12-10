CFLAGS = -Wall -v -pedantic -std=c99 -L/usr/local/lib/ -lhpdf
# LFLAGS = -lm 
BIN = bin
SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
CC = gcc
#PROG = %.o 
# PROG = init.o timesheet.o pdf_printer.o print_table.o last_day.o main.o read_rc_file.o nlist.o	


output: $(OBJ_FILES) 
	$(CC) $(CFLAGS) -o $@ $^ #$(BIN)/output 
	#$(CC) $(CFLAGS) $(addprefix $(BIN)/, $(PROG)) -o $(BIN)/output 
#	$(BIN)/output 1 30 13

$(BIN)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $<

#$(BIN)/main.o: main.c
	#$(CC) -c main.c

# j$(BIN)/pdf_printer.o: pdf_printer.c pdf_printer.h
# j	$(CC) -c -I/Users/muhaye/Py/Timesheet/libharu/include -Ilibharu/include pdf_printer.c 

# j$(BIN)/print_table.o: print_table.c print_table.h
	# j$(CC) -c print_table.c 
	
# j$(BIN)/last_day.o: last_day.c last_day.h
# j	$(CC) -c last_day.c 
	
clean:
	rm -rf $(BIN)/*.o $(BIN)/output
