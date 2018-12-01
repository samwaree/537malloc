CC=gcc
SCAN_BUILD_DIR = scan-build-out
EXE=output
TEST=main

all: $(TEST).o 537malloc.o range_tree.o linked_list.o
	$(CC) -o $(EXE) $(TEST).o 537malloc.o range_tree.o linked_list.o

# main.c is your testcase file name
$(TEST).o: $(TEST).c
	$(CC) -Wall -Wextra -c $(TEST).c

# Include all your .o files in the below rule
obj: 537malloc.o range_tree.o linked_list.o

537malloc.o: 537malloc.c 537malloc.h range_tree.h
	$(CC) -Wall -Wextra -g -O0 -c 537malloc.c

range_tree.o: range_tree.c range_tree.h
	$(CC) -Wall -Wextra -g -O0 -c range_tree.c

linked_list.o: linked_list.c linked_list.h
	$(CC) -Wall -Wextra -g -O0 -c linked_list.c

clean:
	-rm *.o $(EXE)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
