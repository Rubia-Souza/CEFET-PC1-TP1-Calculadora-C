#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "utils/constants.h"
#include "utils/converters.h"

/*
 * Trabalho Prático 1 - Engenharia da Computação CEFET-MG
 * Aluna: Rúbia Alice Moreira de Souza
 */

/*
 * Função que recebe a entrada do usuário no início da execução
 * Por utilizar o fgets, ele lê até os 61 primeiroes caracteres inseridos
 */
void getUserInput(char outExpression[EXPRESSION_SIZE]);

/*
 * Função que faz a verificação da expreção para afimar se ela é válida ou não
 * A expressão não é considerada válida caso haja uma divisão por zero ou
 * caso não haja nenhum operador informado.
 */
bool isExpressionValid(const char operation, const double secondNumber);

/*
 * Função que possui o switch para a identificação de qual operação realizar
 * de acordo com o símbolo informado.
 */
double executeExpression(const double firstNumber, const char operation, const double secondNumber);

/*
 * Função que mantem o loop de entrada para pedir ao usuário se ele deseja
 * fazer mais uma operação ou não
 */
bool askForNextInteration();

/*
 * Função que imprime a estrutura padrão do resultado de saida da operação
 */
void printResult(const double resultValue);

/*
 * Função que imprime a mensagem final do programa e informa o número de 
 * operações realizadas
 */
void printExitMessage(const int succefullOperations);

int main() {
    printf("===== CALCULADORA TP1 - Rúbia Alice =====\n\n");

    char expression[EXPRESSION_SIZE] = "";
    bool shouldContinue = false;
    int interationCount = 0;
    do {
        // Inicialmente o programa pede a entrada da expressão a usuário
        getUserInput(expression);

        // Então o sistema trata a informação extraindo apenas os elementos da expressão matemática
        double firstNumber = 0, secondNumber = 0;
        char operation;
        extractMathematicalExpression(expression, &firstNumber, &operation, &secondNumber);

        // Após isso, ele verifica se a expressão inserida é válida
        if (isExpressionValid(operation, secondNumber)) { // Se sim ela é executada e contabilizada
            printf("Operação: %f %c %f\n", firstNumber, operation, secondNumber);

            double result = executeExpression(firstNumber, operation, secondNumber);
            printResult(result);

            interationCount++;
        }
        else { // Se não, o sistema informa que ela é inválida
            printf("Operador inválido!\n");
        }

        // Depois ele pede a entrada para verificar se deve continuar a execução
        shouldContinue = askForNextInteration();
    } while (shouldContinue);

    // Por fim, ele exibe a mensagem de saida com a quantidade de operações bem sucedidas
    printExitMessage(interationCount);
    return 0;
}

void getUserInput(char outExpression[EXPRESSION_SIZE]) {
    printf("Digite a expressão: ");
    fflush(stdin); // Limpa a entrada do teclado para evitar alguma entrada não desejada do buffer
    fgets(outExpression, EXPRESSION_SIZE, stdin); // Retringe a quantidade de caracters ao EXPRESSION_SIZE para evitar overflow de casas no double
    printf("\n");

    return;
}

bool isExpressionValid(const char operation, const double secondNumber) {
    // Verifica se a expressão não possui um operador
    bool hasSetOperation = operation != '\000';
    if (!hasSetOperation) { // Se sim ela é inválida
        return false;
    }

    // Verifica se a operação é uma divisão por zero
    bool isADivision = operation == '\\' || operation == '/';
    if (isADivision && secondNumber == 0) { // Se sim ela é inválida
        return false;
    }

    return true;
}

double executeExpression(const double firstNumber, const char operation, const double secondNumber) {
    switch (operation) {
        case '+': return  firstNumber + secondNumber; // Os cases não precisam de break, pois o return já evita a passagem para a próxima condição

        case '-': return firstNumber - secondNumber;

        case '*':
        case 'X':
        case 'x': return firstNumber * secondNumber; // Case sem breaks com cases em sequência para aceitar mais de um valor para a multiplicação

        case '\\':
        case '/': return firstNumber / secondNumber; // Case sem breaks com cases em sequência para aceitar mais de um valor para a divisão

        case '^': return pow(firstNumber, secondNumber);
    }

    return 0;
}

bool askForNextInteration() {
    char shouldContinue;

    while (true) { // Mantem o loop infinito que só será encerrado com o retorno da função. Assim, garantindo a entrada válida do usuário
        printf("Você deseja digitar outra expressão (s/n)? ");
        fflush(stdin); // Limpa o buffer do teclado para evitar uma entrada não desejada
        scanf("%c", &shouldContinue);
        getchar();

        if (shouldContinue == 's' || shouldContinue == 'S') {
            return true;
        }
        else if (shouldContinue == 'n' || shouldContinue == 'N') {
            return false;
        }
        else {
            // Informa ao usuário quais valores são aceitos novamente ao receber uma entrada errada
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
