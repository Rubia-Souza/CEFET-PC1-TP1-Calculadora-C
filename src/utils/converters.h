#include "constants.h"

void extractMathematicalExpression(const char expression[EXPRESSION_SIZE], char outFinalExpression[EXPRESSION_SIZE]);void extractMathematicalExpression(const char expression[EXPRESSION_SIZE], double* outFirstNumber, char* outOperation, double* outSecondNumber);
double parseStringToNumber(const char stringNumber[MAX_OPERATION_NUMBERS]);
void parseNumberToString(const double number, char outStringNumber[MAX_OPERATION_NUMBERS]);
