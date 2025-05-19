CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=$(BUILD_DIR)/token.h

BUILD_DIR = build
SAMPLES_DIR = samples
SRC_DIR = src
INCLUDE_DIR = include
START = 1
END = 48

READLINE_FLAGS = -lreadline

INTERACTIVE_OBJ = $(BUILD_DIR)/interactive.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/Expression.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/scanner.o

MPL_OBJ = $(BUILD_DIR)/mpl.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/Expression.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/scanner.o

all: $(BUILD_DIR)/interpreter $(BUILD_DIR)/mpl

$(BUILD_DIR)/interpreter: $(INTERACTIVE_OBJ)
	$(CXX) $^ -o $@ $(READLINE_FLAGS)

$(BUILD_DIR)/mpl: $(MPL_OBJ)
	$(CXX) $^ -o $@

$(BUILD_DIR)/parser.o: $(BUILD_DIR)/parser.c $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/parser.c: parser.bison | $(BUILD_DIR)
	$(BISON) -v --output=$@ $<

$(BUILD_DIR)/scanner.o: $(BUILD_DIR)/scanner.c $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/scanner.c: scanner.flex $(BUILD_DIR)/token.h | $(BUILD_DIR)
	$(FLEX) -o $@ $<

$(BUILD_DIR)/interactive.o: main.cpp $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/mpl.o: mpl.cpp $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/utils.o: $(SRC_DIR)/utils.cpp $(INCLUDE_DIR)/utils.hpp

	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/Expression.o: $(SRC_DIR)/Expression.cpp $(INCLUDE_DIR)/Expression.hpp $(INCLUDE_DIR)/utils.hpp
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/token.h: parser.bison | $(BUILD_DIR)
	$(BISON) --defines=$@ --output=/dev/null $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/interactive.o $(BUILD_DIR)/mpl.o: | $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/interpreter
	./$(BUILD_DIR)/interpreter

mpl: $(BUILD_DIR)/mpl
	@for i in $(shell seq $(START) $(END)); do \
		SAMPLES_FILE="$(SAMPLES_DIR)/$$i-"*.mpl; \
		if [ -f $$(echo $$SAMPLES_FILE | cut -d' ' -f1) ]; then \
			for FILE in $$SAMPLES_FILE; do \
				echo "\nExecuting File: $$FILE"; \
				./$(BUILD_DIR)/mpl "$$FILE"; \
			done; \
		else \
			echo "Archives not found $$i"; \
		fi; \
	done

mplv: $(BUILD_DIR)/mpl
	@for i in $(shell seq $(START) $(END)); do \
		SAMPLES_FILE="$(SAMPLES_DIR)/$$i-"*.mpl; \
		if [ -f $$(echo $$SAMPLES_FILE | cut -d' ' -f1) ]; then \
			for FILE in $$SAMPLES_FILE; do \
				echo "\nExecuting File: $$FILE"; \
				valgrind --leak-check=full ./$(BUILD_DIR)/mpl "$$FILE"; \
			done; \
		else \
			echo "Archives not found $$i"; \
		fi; \
	done

.PHONY: all clean run mpl mplv