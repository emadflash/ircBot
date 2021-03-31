CC = gcc
CFLAGS = -g -Wall -O2 -fsanitize=address 
OBJFILES = irc.o main.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
