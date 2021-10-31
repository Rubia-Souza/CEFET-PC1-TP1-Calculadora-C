#include "constants.h"

// Este arquivo possui definições para converter números, strings e a expressão matemática

/*
 * Esta função analiza a expressão passada para encontrar dois números e um operador válido
 * então ela retorna os valores encotradas nos parâmtros por referência
 * Caso não encontre números eles serão considerados 0
 * Caso não encontre o operador ela irá retornar uma string vazia '\000'
 */
void extractMathematicalExpression(const char expression[EXPRESSION_SIZE], char outFinalExpression[EXPRESSION_SIZE]);void extractMathematicalExpression(const char expression[EXPRESSION_SIZE], double* outFirstNumber, char* outOperation, double* outSecondNumber);

/*
 * Esta função realiza a conversão de uma string para um número double
 * Ela faz tratamentos próprios para formatar o número no padrão ideal
 * então utiliza uma função predefinida para a conversão
 */
double parseStringToNumber(const char stringNumber[MAX_OPERATION_NUMBERS]);

/*
 * Esta função realiza a conversão de um número para uma string
 */
void parseNumberToString(const double number, char outStringNumber[MAX_OPERATION_NUMBERS]);
