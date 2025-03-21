CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=token.h

TEST_DIR = ../samples
START = 1
END = 29

all: validator

validator: parser.o scanner.o main.o
	$(CXX) scanner.o parser.o main.o -o validator

parser.o: parser.c
	$(CXX) -c parser.c

parser.c: parser.bison
	$(BISON) -v --output parser.c parser.bison

scanner.o: token.h scanner.c
	$(CXX) -c scanner.c

scanner.c: scanner.flex
	$(FLEX) -o scanner.c scanner.flex

main.o: token.h main.c
	$(CXX) -c main.c

.PHONY:
clean:
	$(RM) *.o parser.c parser.output token.h scanner.c validator

run: validator
	@for i in $(shell seq $(START) $(END)); do \
		TEST_FILE="$(TEST_DIR)/$$i-"*.mpl; \
		if [ -f $$(echo $$TEST_FILE | cut -d' ' -f1) ]; then \
			for FILE in $$TEST_FILE; do \
				echo "\nTesting Samples: $$FILE"; \
				./validator "$$FILE"; \
			done; \
		else \
			echo "Archives not found $$i"; \
		fi; \
	done