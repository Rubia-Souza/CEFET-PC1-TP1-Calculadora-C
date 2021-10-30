#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/constants.h"

void formatExpression(char expression[EXPRESSION_SIZE]);
int getArrayUsedSize(char expression[EXPRESSION_SIZE], char finalIndicator);
int findOperationSign(char expression[EXPRESSION_SIZE], int size);
void splitExpressionByOperator(char expression[EXPRESSION_SIZE], int operatorIndex, int size, char outFirstNumber[MAX_OPERATION_NUMBERS], char outSecondNumber[MAX_OPERATION_NUMBERS]);
double parseNumber(char stringNumber[MAX_OPERATION_NUMBERS]);

int main() {
    char expression[EXPRESSION_SIZE] = "";
    char formattedExpression[EXPRESSION_SIZE] = "";
    int filledSize = 0;

    printf("===== CALCULADORA TP1 =====\n\n");

    printf("Digite a expressão: ");
    fgets(expression, EXPRESSION_SIZE, stdin);
    printf("\n");

    formatExpression(expression);

    return 0;
}

void formatExpression(char expression[EXPRESSION_SIZE]) {
    int usedSize = getArrayUsedSize(expression, '\n');
    int operatorIndex = findOperationSign(expression, usedSize);
    char operation = expression[operatorIndex];

    char firstStringNumber[MAX_OPERATION_NUMBERS] = "";
    char secondStringNumber[MAX_OPERATION_NUMBERS] = "";
    splitExpressionByOperator(expression, operatorIndex, usedSize, firstStringNumber, secondStringNumber);

    double firstNumber = parseNumber(firstStringNumber);
    double secondNumber = parseNumber(secondStringNumber); 
}

int getArrayUsedSize(char expression[EXPRESSION_SIZE], char finalIndicator) {
    int count = 0;
    for (int i = 0; i < EXPRESSION_SIZE; i++) {
        if (expression[i] == finalIndicator) {
            break;
        }
        else {
            count ++;
        }
    }

    return count;
}

int findOperationSign(char expression[EXPRESSION_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < VALID_OPERATIONS_SIZE; j++) {
            if (expression[i] == VALID_OPERATIONS[j]) {
                return i;
            }
        }
    }

    return -1;
}

void splitExpressionByOperator(char expression[EXPRESSION_SIZE], int operatorIndex, int size, char outFirstNumber[MAX_OPERATION_NUMBERS], char outSecondNumber[MAX_OPERATION_NUMBERS]) {
    for (int i = 0, n1Index = 0, n2Index = 0; i < size; i++) {
        if (i < operatorIndex) {
            outFirstNumber[n1Index] = expression[i];
            n1Index++;
        }
        else if (i > operatorIndex) {
            outSecondNumber[n2Index] = expression[i];
            n2Index++;
        }
    }
}

double parseNumber(char stringNumber[MAX_OPERATION_NUMBERS]) {
    const char VALID_CHARACTERS[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '.'};

    int size = getArrayUsedSize(stringNumber, '\000');

    int formattedStringNumberIndex = 0;
    char formattedStringNumber[MAX_OPERATION_NUMBERS] = "";
    bool dotIsValid = true;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 12; j++) {
            char character = stringNumber[i];

            if (character == VALID_CHARACTERS[j]) {
                bool characterIsDot = character == ',' || character == '.';
                if (dotIsValid && characterIsDot) {
                    dotIsValid = false;
                    character = '.';
                    formattedStringNumber[formattedStringNumberIndex] = stringNumber[i];
                    formattedStringNumberIndex++;
                }
                else if (!characterIsDot) {
                    formattedStringNumber[formattedStringNumberIndex] = stringNumber[i];
                    formattedStringNumberIndex++;
                }
            }
        }
    }

    return strtod(formattedStringNumber, NULL);
}
