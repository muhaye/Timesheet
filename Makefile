CFLAGS = -g -Wall -v -pedantic -std=c99 -L/usr/local/lib/ -lhpdf -Ilibharu/include

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

#./all --work r1-21 --off d12,13,14
#./all --work r1-21 --off r5-15

all: $(OBJECTS)
	$(CC) $(CFLAGS)  $^ -o $@

all_g: $(OBJECTS)
	$(CC) $(CFLAGS)  $^ -g -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) -g -c $< -o $@

clean:
	rm -f $(OBJ)/*o all
