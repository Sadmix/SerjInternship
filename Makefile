.PHONY: build test

all: build test

build:
	gcc test.c -lcunit -lgsl -o test

test:
	./test
	
