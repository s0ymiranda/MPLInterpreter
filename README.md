# Interpreter for the Mathematical Programming Language

## Project Description

This project focuses on developing an interpreter for the "Mathematical Programming Language," which was created in a previous course titled “Programming Languages.” The primary objective is to enhance the usability of the language, allowing users to interact with it in a more intuitive and efficient manner.

The Mathematical Programming Language was designed to solve fundamental mathematics problems through numerical methods, providing simplified access to various mathematical algorithms. This language allows tasks such as calculating the determinant of a matrix or solving integrals using the Simpson's method, among other functionalities.

## Features of the Interpreter

- **Lexical Analyzer:** Currently, the interpreter includes a lexical analyzer implemented using Flex and C found in the scannerFlex folder. This component is essential for breaking down the source code into tokens.

- **Syntactic Validator:** Currently, the interpreter includes a syntactic validator implemented using Bison and C++ found in the parserBison folder. This component is essential ensuring that the sequence of tokens follows the syntactic rules defined for the language.

## Installation and Usage Instructions

1. **Prerequisites:**
   - Ensure you have Flex, Bison and Make installed on your system.
   - Have a C and C++ compiler (such as GCC) available.

2. **Clone the Repository:**

3. **Acces the scannerFlex folder or parserBison folder**

4.  **Compile the Proyect**
    - There is a makefile provider for the scanner and parser.   
   ```bash
     make
     make clean
   ```

5. **Run the scanner or the parser**

   There is several samples for the language, in the samples folder.
   You can run then individually, example:
   ```bash
     ./scanner <source code>
     ./validator <source code>
   ```
   Or run all the examples with:
   ```bash
     make run
   ```


## Acknowledgements
For more information about the development and specifications of the Mathematical Programming Language, you can refer to 
- [Mathematical Programming Lenguage Repository](https://github.com/gerardorosetti/programming_languages_project).
