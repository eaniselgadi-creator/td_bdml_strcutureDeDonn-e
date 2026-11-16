# Makefile du TD BDML (alternative a CMake pour compiler dans un terminal)
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ    = main.o flower.o list.o dataset.o knn.o queue.o sensor.o stack.o json_check.o

td_bdml: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lm

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

run: td_bdml
	./td_bdml

clean:
	rm -f *.o td_bdml
