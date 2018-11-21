CC=gcc
WARNING_FLAGS=-Wall -Wextra
SCAN_BUILD_DIR = scan-build-out

537malloc.o: 537malloc.c 537malloc.h range_tree.c range_tree.h
	$(CC) -g $(WARNING_FLAGS) -c 537malloc.c range_tree.c

clean:
	rm *.o
