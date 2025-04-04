#include <iostream>
#include <fstream>
#include "Expression.hpp"
#include "utils.hpp"

extern FILE* yyin;
extern int yyparse();
extern Expression* parser_result;

void printAST(Expression* expr, int depth = 0) {
    if (!expr) return;

    // Indentación para mostrar la estructura del árbol
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }

    // Imprimir el tipo de nodo y su representación
    std::cout << "- " << expr->toString() << std::endl;

    // Si es una expresión binaria, imprimir sus hijos
    if (auto binExpr = dynamic_cast<BinaryExpression*>(expr)) {
        printAST(binExpr->getLeftExpression(), depth + 1);
        printAST(binExpr->getRightExpression(), depth + 1);
    }
    // Si es una expresión unaria, imprimir su hijo
    else if (auto unaryExpr = dynamic_cast<UnaryExpression*>(expr)) {
        printAST(unaryExpr->getExpression(), depth + 1);
    }
    // Si es una lista de expresiones, imprimir cada elemento
    else if (auto listExpr = dynamic_cast<ExpressionList*>(expr)) {
        for (auto e : listExpr->getVectorExpression()) {
            printAST(e, depth + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Abrir el archivo de entrada
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    // Ejecutar el parser
    int result = yyparse();
    fclose(yyin);

    if (result == 0) {
        std::cout << "Parsing successful! AST:" << std::endl;
        std::cout << "=======================" << std::endl;
        
        // Imprimir el AST
        if (parser_result) {
            printAST(parser_result);
        } else {
            std::cout << "No AST generated." << std::endl;
        }
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    // Liberar memoria
    if (parser_result) {
        parser_result->destroy();
        delete parser_result;
    }

    return 0;
}