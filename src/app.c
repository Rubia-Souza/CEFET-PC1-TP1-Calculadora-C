#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/constants.h"
#include "utils/converters.h"

// Calculo é executado segundo a ordem de escrita de NUM OP NUM. Se não ouver um NUM ele é considerado 0.
int main() {
    char expression[EXPRESSION_SIZE] = "";

    printf("===== CALCULADORA TP1 - Rúbia Alice =====\n\n");

    printf("Digite a expressão: ");
    fgets(expression, EXPRESSION_SIZE, stdin);
    printf("\n");

    double firstNumber = 0, secondNumber = 0;
    char operation;

    extractMathematicalExpression(expression, &firstNumber, &operation, &secondNumber);

    printf("Operação: %f%c%f", firstNumber, operation, secondNumber);

    return 0;
}


