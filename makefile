CC = gcc
CFLAGS = -g -Wall -fsanitize=address 
OBJFILES = irc.o main.o parser.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
