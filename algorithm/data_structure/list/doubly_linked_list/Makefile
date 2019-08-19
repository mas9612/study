CPP := c++
LIB := dll.o

.PHONY: all
all: test build

.PHONY: build
build:
	$(CPP) -o $(LIB) -c ./doubly_linked_list.cpp

.PHONY: clean
clean:
	rm -f $(LIB)

.PHONY: test
test:
	$(CPP) -o test ./test.cpp ./doubly_linked_list.cpp
	./test
	rm -f test
