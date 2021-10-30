#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h"
#include "converters.h"
# include "utils.h"

int findOperationSign(const char expression[EXPRESSION_SIZE], const int size);
void splitExpressionByOperator(const char expression[EXPRESSION_SIZE], const int operatorIndex, const int size, char outFirstNumber[MAX_OPERATION_NUMBERS], char outSecondNumber[MAX_OPERATION_NUMBERS]);
void filterValidCharacter(const char target[], const int size, char outString[]);
void removeExtraDots(const char target[], const int size, char outString[]);
double compleateDecimalNumber(const char stringNumber[MAX_OPERATION_NUMBERS]);

void extractExpression(const char expression[EXPRESSION_SIZE]) {
    int usedSize = getArrayUsedSize(expression, '\n');
    int operatorIndex = findOperationSign(expression, usedSize);
    char operation = expression[operatorIndex];

    char part1[MAX_OPERATION_NUMBERS] = "";
    char part2[MAX_OPERATION_NUMBERS] = "";
    splitExpressionByOperator(expression, operatorIndex, usedSize, part1, part2);
    
    char filteredPart1[MAX_OPERATION_NUMBERS] = "";
    char filteredPart2[MAX_OPERATION_NUMBERS] = "";
    filterValidCharacter(part1, MAX_OPERATION_NUMBERS, filteredPart1);
    filterValidCharacter(part2, MAX_OPERATION_NUMBERS, filteredPart2);

    char formattedStringPart1[MAX_OPERATION_NUMBERS] = "";
    char formattedStringPart2[MAX_OPERATION_NUMBERS] = "";
    removeExtraDots(filteredPart1, MAX_OPERATION_NUMBERS, formattedStringPart1);
    removeExtraDots(filteredPart2, MAX_OPERATION_NUMBERS, formattedStringPart2);

    double firstNumber = parseNumber(formattedStringPart1);
    double secondNumber = parseNumber(formattedStringPart2); 
}

double parseNumber(const char stringNumber[MAX_OPERATION_NUMBERS]) {
    bool firstPositionIsADot = stringNumber[0] == '.';
    bool isStringJustDot = firstPositionIsADot && stringNumber[1] == '\n';
    bool isStringEmpty = stringNumber == "";

    if (isStringEmpty || isStringJustDot) {
        return 0.0;
    }

    if (firstPositionIsADot) {
        return compleateDecimalNumber(stringNumber);
    }

    return strtod(stringNumber, NULL);
}


int findOperationSign(const char expression[EXPRESSION_SIZE], const int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < VALID_OPERATIONS_SIZE; j++) {
            if (expression[i] == VALID_OPERATIONS[j]) {
                return i;
            }
        }
    }

    return -1;
}

void splitExpressionByOperator(const char expression[EXPRESSION_SIZE], const int operatorIndex, const int size, char outFirstNumber[MAX_OPERATION_NUMBERS], char outSecondNumber[MAX_OPERATION_NUMBERS]) {
    int n1Index = 0, n2Index = 0;

    for (int i = 0; i < size; i++) {
        if (i < operatorIndex) {
            outFirstNumber[n1Index] = expression[i];
            n1Index++;
        }
        else if (i > operatorIndex) {
            outSecondNumber[n2Index] = expression[i];
            n2Index++;
        }
    }

    return;
}

void filterValidCharacter(const char target[], const int size, char outString[]) {
    int outStringIndex = 0;

    for (int i = 0; i < size; i++) {
        bool isValidCharacter = contaisElement(VALID_CHARACTERS, target[i], VALID_CHARACTERS_SIZE);

        if (isValidCharacter) {
            outString[outStringIndex] = target[i];
            outStringIndex++;
        }
    }

    outString[outStringIndex] = '\n';

    return;
}

void removeExtraDots(const char target[], const int size, char outString[]) {
    int outStringIndex = 0;
    bool dotIsValid = true;

    for (int i = 0; i < size; i++) {
        char character = target[i]; 
        bool characterIsDot = character == ',' || character == '.';

        if (dotIsValid && characterIsDot) {
            dotIsValid = false;
            character = '.';
            outString[outStringIndex] = character;
            outStringIndex++;
        }
        else if (!characterIsDot) {
            outString[outStringIndex] = character;
            outStringIndex++;
        }
    }

    return;
}

double compleateDecimalNumber(const char stringNumber[MAX_OPERATION_NUMBERS]) {
    char stringNumberCopy[MAX_OPERATION_NUMBERS] = "";
    strcpy(stringNumberCopy, stringNumber);
    
    int size = getArrayUsedSize(stringNumberCopy, '\n');
    char lastPosition = stringNumberCopy[0];
    stringNumberCopy[0] = '0';

    for (int i = 1; i <= size; i++) {
        char temp = stringNumberCopy[i];
        stringNumberCopy[i] = lastPosition;
        lastPosition = temp;
    }

    return strtod(stringNumberCopy, NULL); // TODO: see how to parse 0.x numbers
}
