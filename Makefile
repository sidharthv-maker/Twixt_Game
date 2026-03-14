CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = play
OBJS = functions.o main.o
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c
main.o: main.c functions.h
	$(CC) $(CFLAGS) -c main.c
play: $(TARGET)
clean:
	rm -f *.o $(TARGET)