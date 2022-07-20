CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread
DEP = list.h
FILES = list.c main.c
OBJFILES = list.o main.o
TARGET = main

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

list.o: list.c $(DEP)
	$(CC) $(CFLAGS) -c list.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJFILES) $(TARGET)