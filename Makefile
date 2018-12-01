CC=gcc
WARNING_FLAGS=-Wall -Wextra
SCAN_BUILD_DIR = scan-build-out

obj: 537malloc.o range_tree.o linked_list.o

range_tree.o: range_tree.c range_tree.h linked_list.o
	$(CC) -g $(WARNING_FLAGS) -c range_tree.c

linked_list.o: linked_list.c linked_list.h
	$(CC) -g $(WARNING_FLAGS) -c linked_list.c

537malloc.o: 537malloc.c 537malloc.h range_tree.o
	$(CC) -g $(WARNING_FLAGS) -c 537malloc.c

test: obj test.c
	

clean:
	rm *.o
