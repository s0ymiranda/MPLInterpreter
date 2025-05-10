# Interpreter for the Mathematical Programming Language

## Project Description

This project focuses on developing an interpreter for the "Mathematical Programming Language," which was created in a previous course titled “Programming Languages.” The primary objective is to enhance the usability of the language, allowing users to interact with it in a more intuitive and efficient manner.

The Mathematical Programming Language was designed to solve fundamental mathematics problems through numerical methods, providing simplified access to various mathematical algorithms. This language allows tasks such as calculating the determinant of a matrix or solving integrals using the Simpson's method, among other functionalities.

## Features of the Interpreter

- **Lexical Analyzer:** Currently, the interpreter includes a lexical analyzer implemented using Flex and C, the "scanner.flex" file.

- **Syntactic Validator:** Currently, the interpreter includes a syntactic validator implemented using Bison and C++ the "parser.bison" file.

- **Abstract Syntax Tree:** Currenty from the Syntactic Validator it is constructed an AST.

## Installation and Usage Instructions

1. **Prerequisites:**
   - Ensure you have Flex, Bison and Make installed on your system.
   - Have a C and C++ compiler (such as GCC) available.
   - To use the interactive interpreter, it is required to install the Readline library. You can do it in Ubuntu just by executing: sudo apt-get install libreadline-dev.

2. **Clone the Repository:**

3.  **Compile the Proyect**
    - There is a makefile provide.
   ```bash
     make
     make clean
   ```

4. **Run the parser**
    There is provide a make run, that uses the interactive interpreter:
   ```bash
      make run
   ```
   Also you can run all the files in the samples folder by using make test:
   ```bash
      make test
   ```
   Or run the samples individually:
   ```bash
      ./build/parser /samples/"name of the file"
   ```


## Acknowledgements
For more information about the development and specifications of the Mathematical Programming Language, you can refer to
- [Mathematical Programming Lenguage Repository](https://github.com/gerardorosetti/programming_languages_project).
