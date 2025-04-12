CXX = g++ -O0 -g
FLEX = flex
BISON = bison -Wcounterexamples --defines=$(INCLUDE_DIR)/token.h

BUILD_DIR = build
TEST_DIR = samples
SRC_DIR = src
INCLUDE_DIR = include
START = 1
END = 34

OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/Expression.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/scanner.o

all: $(BUILD_DIR)/parser

$(BUILD_DIR)/parser: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

$(BUILD_DIR)/parser.o: $(BUILD_DIR)/parser.c
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/parser.c: parser.bison
	$(BISON) -v --output=$@ $<

$(BUILD_DIR)/scanner.o: $(BUILD_DIR)/scanner.c
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/scanner.c: scanner.flex
	$(FLEX) -o $@ $<

$(BUILD_DIR)/main.o: main.cpp $(INCLUDE_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/Expression.o: $(SRC_DIR)/Expression.cpp $(INCLUDE_DIR)/Expression.hpp $(INCLUDE_DIR)/utils.hpp
	$(CXX) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: | $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/parser
	@for i in $(shell seq $(START) $(END)); do \
		TEST_FILE="$(TEST_DIR)/$$i-"*.mpl; \
		if [ -f $$(echo $$TEST_FILE | cut -d' ' -f1) ]; then \
			for FILE in $$TEST_FILE; do \
				echo "\nTesting Samples: $$FILE"; \
				./$(BUILD_DIR)/parser "$$FILE"; \
			done; \
		else \
			echo "Archives not found $$i"; \
		fi; \
	done