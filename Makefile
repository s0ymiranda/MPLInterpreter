CXX = g++
FLEX = flex
BISON = bison -Wcounterexamples --defines=$(BUILD_DIR)/token.h

BUILD_DIR = build
TEST_DIR = samples
SRC_DIR = src
INCLUDE_DIR = include
START = 1
END = 35

READLINE_FLAGS = -lreadline -lncurses

# Objetos para el intérprete interactivo
INTERACTIVE_OBJ = $(BUILD_DIR)/interactive.o $(BUILD_DIR)/Expression.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/scanner.o

# Objetos para los tests
TEST_OBJ = $(BUILD_DIR)/test.o $(BUILD_DIR)/Expression.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/scanner.o

all: $(BUILD_DIR)/interpreter $(BUILD_DIR)/test

# Regla para el intérprete interactivo
$(BUILD_DIR)/interpreter: $(INTERACTIVE_OBJ)
	$(CXX) $^ -o $@ $(READLINE_FLAGS)

# Regla para los tests
$(BUILD_DIR)/test: $(TEST_OBJ)
	$(CXX) $^ -o $@

# Reglas para el parser y scanner
$(BUILD_DIR)/parser.o: $(BUILD_DIR)/parser.c $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/parser.c: parser.bison | $(BUILD_DIR)
	$(BISON) -v --output=$@ $<

$(BUILD_DIR)/scanner.o: $(BUILD_DIR)/scanner.c $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/scanner.c: scanner.flex $(BUILD_DIR)/token.h | $(BUILD_DIR)
	$(FLEX) -o $@ $<

# Objeto para el intérprete interactivo
$(BUILD_DIR)/interactive.o: main.cpp $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

# Objeto para los tests
$(BUILD_DIR)/test.o: test.cpp $(BUILD_DIR)/token.h
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/Expression.o: $(SRC_DIR)/Expression.cpp $(INCLUDE_DIR)/Expression.hpp $(INCLUDE_DIR)/utils.hpp
	$(CXX) -I$(INCLUDE_DIR) -I$(BUILD_DIR) -c $< -o $@

# Generación explícita de token.h
$(BUILD_DIR)/token.h: parser.bison | $(BUILD_DIR)
	$(BISON) --defines=$@ --output=/dev/null $<

# Creación del directorio build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Dependencias de orden
$(BUILD_DIR)/interactive.o $(BUILD_DIR)/test.o: | $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Ejecuta el intérprete interactivo
run: $(BUILD_DIR)/interpreter
	./$(BUILD_DIR)/interpreter

# Ejecuta los tests (similar a tu antiguo 'make run')
test: $(BUILD_DIR)/test
	@for i in $(shell seq $(START) $(END)); do \
		TEST_FILE="$(TEST_DIR)/$$i-"*.mpl; \
		if [ -f $$(echo $$TEST_FILE | cut -d' ' -f1) ]; then \
			for FILE in $$TEST_FILE; do \
				echo "\nTesting Samples: $$FILE"; \
				./$(BUILD_DIR)/test "$$FILE"; \
			done; \
		else \
			echo "Archives not found $$i"; \
		fi; \
	done

.PHONY: all clean run test