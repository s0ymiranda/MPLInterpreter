# Interpreter for the Mathematical Programming Language

## Project Description

This project focuses on developing an interpreter for the "Mathematical Programming Language," which was created in a previous course titled “Programming Languages.” The primary objective is to enhance the usability of the language, allowing users to interact with it in a more intuitive and efficient manner.

The Mathematical Programming Language was designed to solve fundamental mathematics problems through numerical methods, providing simplified access to various mathematical algorithms. This language allows tasks such as calculating the determinant of a matrix or solving integrals using the Simpson's method, among other functionalities.

## Features of the Interpreter

- **Lexical Analyzer:** Currently, the interpreter includes a lexical analyzer implemented using Flex and C, the "scanner.flex" file.

- **Syntactic Validator:** Currently, the interpreter includes a syntactic validator implemented using Bison and C++ the "parser.bison" file.

- **Abstract Syntax Tree:** Currenty from the Syntactic Validator it is constructed an AST.

- **Semantic Analysis:** Evaluation Methods, that verify the semantic validity of the expressions. Use an Environment to maintain the program's state, including variables and their values, and to assist in identifier resolution.

## Installation and Usage Instructions

1. **Prerequisites:**
   - Ensure you have Flex, Bison and Make installed on your system.
   - Have a C and C++ compiler (such as GCC) available.

2. **Clone the Repository:**

3.  **Compile the Proyect**
    - There is a makefile provide.
   ```bash
     make
     make clean
   ```

4. **Run the parser**
    There is provide a make run, that uses all the files in the samples folder
   ```bash
      make run
   ```
   Or run the samples individually:
   ```bash
      ./build/parser /samples/"name of the file"
   ```
## Note
   In the samples folder you can found examples usages for the lenguage. So you can make your own scripts of our lenguage and test then!. 
   Currently the main.cpp archive obtains the AST from the parser and evaluates it with the eval method and show the result with the toString method. 

## Acknowledgements
For more information about the development and specifications of the Mathematical Programming Language, you can refer to
- [Mathematical Programming Lenguage Repository](https://github.com/gerardorosetti/programming_languages_project).
