#include "constants.h"

// Este arquivo define funções genéricas que poderiam ser usadas em diversas partes do sistema

/*
 * Função que verifica o tamanho de uma array até encontrar o character finalIndicator
 */
int getArrayUsedSize(const char expression[EXPRESSION_SIZE], const char finalIndicator);

/*
 * Função que verifica se um elemento está presente dentro de um array
 * Retorna true caso encontre e false caso contrário
 */
bool contaisElement(const char expression[], const char checkElement, const int size);
