#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "utils/constants.h"
#include "utils/converters.h"

void getUserInput(char outExpression[EXPRESSION_SIZE]);
bool isExpressionValid(const char operation, const double secondNumber);
double executeExpression(const double firstNumber, const char operation, const double secondNumber);
bool askForNextInteration();
void printResult(const double resultValue);
void printExitMessage(const int succefullOperations);

// Calculo é executado segundo a ordem de escrita de NUM OP NUM. Se não ouver um NUM ele é considerado 0.
int main() {
    printf("===== CALCULADORA TP1 - Rúbia Alice =====\n\n");

    char expression[EXPRESSION_SIZE] = "";
    bool shouldContinue = false;
    int interationCount = 0;
    do {
        getUserInput(expression);

        double firstNumber = 0, secondNumber = 0;
        char operation;
        extractMathematicalExpression(expression, &firstNumber, &operation, &secondNumber);

        if (isExpressionValid(operation, secondNumber)) {
            printf("Operação: %f %c %f\n", firstNumber, operation, secondNumber);

            double result = executeExpression(firstNumber, operation, secondNumber);
            printResult(result);

            interationCount++;
        }
        else {
            printf("Operador inválido!\n");
        }

        shouldContinue = askForNextInteration();
    } while (shouldContinue);

    printExitMessage(interationCount);
    return 0;
}

void getUserInput(char outExpression[EXPRESSION_SIZE]) {
    printf("Digite a expressão: ");
    fgets(outExpression, EXPRESSION_SIZE, stdin);
    printf("\n");

    return;
}

bool isExpressionValid(const char operation, const double secondNumber) {
    bool hasSetOperation = operation != '\000';
    if (!hasSetOperation) {
        return false;
    }

    bool isADivision = operation == '\\' || operation == '/';
    if (isADivision && secondNumber == 0) {
        return false;
    }

    return true;
}

double executeExpression(const double firstNumber, const char operation, const double secondNumber) {
    switch (operation) {
        case '+': return  firstNumber + secondNumber;

        case '-': return firstNumber - secondNumber;

        case '*':
        case 'X':
        case 'x': return firstNumber * secondNumber;

        case '\\':
        case '/': return firstNumber / secondNumber;

        case '^': return pow(firstNumber, secondNumber);
    }

    return 0;
}

bool askForNextInteration() {
    char shouldContinue;

    while (true) {
        printf("Você deseja digitar outra expressão (s/n)? ");
        scanf("%c", &shouldContinue);
        getchar();

        if (shouldContinue == 's' || shouldContinue == 'S') {
            return true;
        }
        else if (shouldContinue == 'n' || shouldContinue == 'N') {
            return false;
        }
        else {
            printf("\nInsira uma entrada válida:\n");
            printf("[s] ou [S] para continuar\n");
            printf("[n] ou [N] para encerrar\n");
        }
    }
}

void printResult(const double resultValue) {
    printf("Resultado: %f\n", resultValue);

    return;
}

void printExitMessage(const int succefullOperations) {
    printf("Foram calculadas %d expressões válidas.\n", succefullOperations);
    printf("Tchau!\n");
    printf("____________________________________________\n");

    return;
}
