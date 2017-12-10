CFLAGS = -Wall -v -pedantic -std=c99 -L/usr/local/lib/ -lhpdf -Ilibharu/include

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: $(OBJECTS)
	$(CC) $(CFLAGS)  $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) -c $< -o $@

clean:
	rm -f $(OBJ)/*o all
