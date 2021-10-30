#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/constants.h"
#include "utils/converters.h"

int main() {
    char expression[EXPRESSION_SIZE] = "";
    char formattedExpression[EXPRESSION_SIZE] = "";
    int filledSize = 0;

    printf("===== CALCULADORA TP1 =====\n\n");

    printf("Digite a expressão: ");
    fgets(expression, EXPRESSION_SIZE, stdin);
    printf("\n");

    extractExpression(expression);

    return 0;
}


