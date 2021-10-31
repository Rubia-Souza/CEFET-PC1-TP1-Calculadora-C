#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "converters.h"
#include "utils.h"

// Este arquivo possui as implementações das funções definidas em converters.h

// As funções abaixo são funções não expostas no .h por serem de contexto bem esepcífico para funcionamento interno das funções publicas

/*
 * Esta função busca um dos operadores válidos dentro da expressão passada
 * Caso ela encontre o operador dentro da string ela retorna sua posição
 * Caso ela não encontre ela retorna -1
 */
int findOperationSign(const char expression[EXPRESSION_SIZE], const int size);

/*
 * Esta função separa os caracteres da expressão, usando como base o operador
 * A saida 1 será todos os caracteres anteriores ao operador
 * A saida 2 será todos os caracteres posteriores ao operador
 */
void splitExpressionByOperator(const char expression[EXPRESSION_SIZE], const int operatorIndex, const int size, char outFirstNumber[MAX_OPERATION_NUMBERS], char outSecondNumber[MAX_OPERATION_NUMBERS]);

/*
 * Esta função remove todo caracter inválido de uma string
 * Ela mantem apenas números entre 0 e 9 e '.'
 */
void filterValidCharacter(const char target[], const int size, char outString[]);

/*
 * Esta função busca por pontos extras em números a fim de manter apenas
 * o primeiro encontrado como representante do início das casas decimais
 */
void removeExtraDots(const char target[], const int size, char outString[]);

/*
 * Esta função verifica se um número não possui parte inteira anterior a vírgula
 * Caso sim, ela é completada com 0
 * Caso o número não tenha valores antes e nem depois da vírgula ele é completado como 0.0
 */
double compleateDecimalNumber(const char stringNumber[MAX_OPERATION_NUMBERS]);

void extractMathematicalExpression(const char expression[EXPRESSION_SIZE], double* outFirstNumber, char* outOperation, double* outSecondNumber) {
    // Inicialmente ela busca pelo PRIMEIRO operador da expressão
    int usedSize = getArrayUsedSize(expression, '\n');
    int operatorIndex = findOperationSign(expression, usedSize);

    char operation;
    if (operatorIndex > -1) {
        operation = expression[operatorIndex];
    }
    else { // caso ela não encontre o operador ele recebe uma string vazia
        operation = '\000';
    }

    // Apos isso, o pregrama separa a string pelo operador em duas partes (antes e depois)
    char part1[MAX_OPERATION_NUMBERS] = "";
    char part2[MAX_OPERATION_NUMBERS] = "";
    splitExpressionByOperator(expression, operatorIndex, usedSize, part1, part2);
    
    // Então, para cada uma das partes ele remove os caracteres inválidos
    char filteredPart1[MAX_OPERATION_NUMBERS] = "";
    char filteredPart2[MAX_OPERATION_NUMBERS] = "";
    filterValidCharacter(part1, MAX_OPERATION_NUMBERS, filteredPart1);
    filterValidCharacter(part2, MAX_OPERATION_NUMBERS, filteredPart2);

    // Depois ele realiza a formatação dos números em forma decimal afim de evitar algum erro na conversão
    char formattedStringPart1[MAX_OPERATION_NUMBERS] = "";
    char formattedStringPart2[MAX_OPERATION_NUMBERS] = "";
    removeExtraDots(filteredPart1, MAX_OPERATION_NUMBERS, formattedStringPart1);
    removeExtraDots(filteredPart2, MAX_OPERATION_NUMBERS, formattedStringPart2);

    // Por fim, ele atribui a saída aos ponteiros com os números já convertidos para double
    *outFirstNumber = parseStringToNumber(formattedStringPart1);
    *outOperation = operation;
    *outSecondNumber = parseStringToNumber(formattedStringPart2);

    return;
}

double parseStringToNumber(const char stringNumber[MAX_OPERATION_NUMBERS]) {
    char copyStringNumber[MAX_OPERATION_NUMBERS];
    strcpy(copyStringNumber, stringNumber); // A conversão realiza uma copia do array original para evitar alterações não previstas

    // Depois ela realiza as validações dos casos em que os números devem ser completados
    bool firstPositionIsADot = copyStringNumber[0] == '.';
    bool isStringJustDot = firstPositionIsADot && copyStringNumber[1] == '\n';
    bool isStringEmpty = copyStringNumber == "";

    if (isStringEmpty || isStringJustDot) { // O primeiro caso é quando foi informado apenas um '.'
        return 0.0;
    }

    if (firstPositionIsADot) { // O segundo caso é quando o número não posui casas inteiras
        return compleateDecimalNumber(copyStringNumber); // Então ela chama a função para completar o número
    }

    return strtod(copyStringNumber, NULL);
}

void parseNumberToString(const double number, char outStringNumber[MAX_OPERATION_NUMBERS]) {
    snprintf(outStringNumber, MAX_OPERATION_NUMBERS, "%f", number); // snprintf faz a escrita do numero double como uma string no primeiro parâmetro, realizando a conversão
}

int findOperationSign(const char expression[EXPRESSION_SIZE], const int size) {
    // Para cada character na expressão, ele é comparado com o segundo array que possui listada os operadores que são válidos
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < VALID_OPERATIONS_SIZE; j++) {
            if (expression[i] == VALID_OPERATIONS[j]) {
                return i; // Caso encontre um operador válido ela retorna o index dele
            }
        }
    }

    return -1; // Se não ela retorna -1
}

void splitExpressionByOperator(const char expression[EXPRESSION_SIZE], const int operatorIndex, const int size, char outFirstNumber[MAX_OPERATION_NUMBERS], char outSecondNumber[MAX_OPERATION_NUMBERS]) {
    int n1Index = 0, n2Index = 0;

    // A divisão é feita percorrendo a expressão e atribuindo as strings para a respectiva saida usando o index do operador como referência para a distribuição
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

    // Ela verifica se cada caracter do alvo esta presente entre os caracteres válidos
    for (int i = 0; i < size; i++) {
        bool isValidCharacter = contaisElement(VALID_CHARACTERS, target[i], VALID_CHARACTERS_SIZE);

        if (isValidCharacter) { // Se estiver eles são alocados na string de saida
            outString[outStringIndex] = target[i];
            outStringIndex++;
        }
    }

    outString[outStringIndex] = '\n'; // A string de saida é finalizada com um \n para futuras verificações terem a referência do ponto de fim dos valores

    return;
}

void removeExtraDots(const char target[], const int size, char outString[]) {
    int outStringIndex = 0;
    bool dotIsValid = true;

    // Aceita a presença de uma vírgula até encontrar a primeira. Apos isso, ela passa a não inserir mais nenhuma no novo numero construido
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
    strcpy(stringNumberCopy, stringNumber); // Realiza a copia do array para evitar efeitos colaterais da função
    
    // Então, atribui a preimeira posição o valor zero e guarda o valor prévio
    int size = getArrayUsedSize(stringNumberCopy, '\n');
    char lastPosition = stringNumberCopy[0];
    stringNumberCopy[0] = '0';

    // Assim, é possível realizar uma troca sempre do valor anterior com o posterior, deslocando os elementos do array uma posição para frente
    for (int i = 1; i <= size; i++) {
        char temp = stringNumberCopy[i];
        stringNumberCopy[i] = lastPosition;
        lastPosition = temp;
    }

    return strtod(stringNumberCopy, NULL);
}
