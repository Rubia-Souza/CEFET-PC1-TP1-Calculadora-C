#include <stdbool.h>
#include "constants.h"

#include "utils.h"

// Este arquivo contem as implementações das funções definidas no utils.h

int getArrayUsedSize(const char expression[EXPRESSION_SIZE], const char finalIndicator) {
    int count = 0;
    for (int i = 0; i < EXPRESSION_SIZE; i++) { // Ela percorre todo o array expression
        if (expression[i] == finalIndicator) { // até encontrar o caracter final
            break;
        }
        else {
            count ++; // enquanto não encontrá-lo ela incrementa o valor do contador do tamanho do array
        }
    }

    return count;
}

bool contaisElement(const char arrayTest[], const char checkElement, const int size) {
    for (int i = 0; i < size; i++) {
        if (arrayTest[i] == checkElement) { // Percorre o array até encontrar o elemento passado por parâmetro
            return true;
        }
    }

    return false; // caso não encontre até o final ela sai do loop e retorna false
}
