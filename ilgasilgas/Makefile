CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJ = main.o ilgasilgas.o
TARGET = test.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

main.o: main.c ilgasilgas.h
	$(CC) $(CFLAGS) -c main.c

ilgasilgas.o: ilgasilgas.c ilgasilgas.h
	$(CC) $(CFLAGS) -c ilgasilgas.c

clean:
	rm -f $(OBJ) $(TARGET) test.txt