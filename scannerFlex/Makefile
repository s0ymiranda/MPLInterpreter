CC = gcc
FLEX = flex

TEST_DIR = ../samples
START = 1
END = 24

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

run: scanner
	@for i in $(shell seq $(START) $(END)); do \
		TEST_FILE="$(TEST_DIR)/$$i-"*.mpl; \
		if [ -f $$(echo $$TEST_FILE | cut -d' ' -f1) ]; then \
			for FILE in $$TEST_FILE; do \
				echo "\nEjecutando prueba: $$FILE"; \
				./scanner "$$FILE"; \
			done; \
		else \
			echo "No se encontraron archivos para el índice $$i"; \
		fi; \
	done