#include <stdbool.h>
#include "constants.h"
#include "utils.h"

int getArrayUsedSize(const char expression[EXPRESSION_SIZE], const char finalIndicator) {
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

bool contaisElement(const char arrayTest[], const char checkElement, const int size) {
    for (int i = 0; i < size; i++) {
        if (arrayTest[i] == checkElement) {
            return true;
        }
    }

    return false;
}
