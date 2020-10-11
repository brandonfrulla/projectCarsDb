TARGET = cars
LIBS = -lm5
CC = gcc
CFLAGS = -g -Wall -std=c11

.PHONY: default all clean
default: $(TARGET)
$(TARGET): main.o car.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o car.o
main.o: main.c car.h
	$(CC) $(CFLAGS) -c main.c
car.o: car.c car.h
	$(CC) $(CFLAGS) -c car.c
clean:
	-rm -f *.o $(TARGET)