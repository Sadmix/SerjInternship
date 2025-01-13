.PHONY: build test

all: build test

build:
	gcc test.c matrix.c --coverage -lcunit -lgsl -o test

test:
	./test
	
