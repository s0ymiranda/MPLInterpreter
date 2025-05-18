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

1. **Prerequisites (For Debian Distributions Users):**
   - Ensure you have Flex, Bison and Make installed on your system.
   ```bash
      sudo apt-get install flex bison make
   ```
   - Have g++ (C++ Compiler) installed.
   ```bash
      sudo apt-get install g++
   ```
   - To use the interactive interpreter, it is required to install the Readline library.
   ```bash
      sudo apt-get install libreadline-dev
   ```

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
   Also you can run all the files in the samples folder by using make mpl:
   ```bash
      make mpl
   ```
   Or use make mplv to run all the files with valgrind for memory study (required to have valgrind installed)
   ```bash
      make mplv
   ```
   Or run the samples individually:
   ```bash
      ./build/mpl samples/"name of the file".mpl
   ```
## Note
   In the samples folder you can found examples usages for the lenguage. So you can make your own scripts of our lenguage and test then!. 
   Currently the main.cpp archive obtains the AST from the parser and evaluates it with the eval method and show the result with the toString method. 

## Acknowledgements
For more information about the development and specifications of the Mathematical Programming Language, you can refer to
- [Mathematical Programming Lenguage Repository](https://github.com/gerardorosetti/programming_languages_project).

For more information about the development and specifications of the Interpreter Mathematical Programming Language, you can read the development document
- [Interpreter - MPL](https://docs.google.com/document/d/1WaoRi4Mnx79ktCwaNhNpfZGid2FKVRdQkL1OfwEX-Rc/edit?tab=t.0#heading=h.rwigb3anhsnq)
