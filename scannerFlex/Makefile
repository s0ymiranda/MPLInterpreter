CC = gcc
FLEX = flex

all: scanner

scanner: scanner.o main.o
	$(CC) scanner.o main.o -o $@

scanner.o: scanner.c token.h
	$(CC) -c $< -o $@

scanner.c: scanner.flex
	$(FLEX) -o $@ $<

main.o: main.c token.h
	$(CC) -c $< -o $@

.PHONY:
clean:
	$(RM) *.o scanner.c scanner