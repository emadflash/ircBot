CC = gcc
CFLAGS = -g -Wall -fsanitize=address 
OBJFILES = buil/irc.o buil/main.o buil/parser.o
TARGET = build/main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
