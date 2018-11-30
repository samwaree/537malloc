CC=gcc
WARNING_FLAGS=-Wall -Wextra
SCAN_BUILD_DIR = scan-build-out

all: main.o range_tree.o
	$(CC) -g -o main main.o range_tree.o

main.o: main.c
	$(CC) -g $(WARNING_FLAGS) -c main.c

range_tree.o: range_tree.c range_tree.h
	$(CC) -g $(WARNING_FLAGS) -c range_tree.c

537malloc.o: 537malloc.c 537malloc.h range_tree.c range_tree.h
	$(CC) -g $(WARNING_FLAGS) -c 537malloc.c range_tree.c

clean:
	rm *.o main
