// Este é o arquvi header para a definição das constantes do sistema

// Inicialmente são definidos os tamanhos máximos padrões dos arrays
#define EXPRESSION_SIZE 61
#define MAX_OPERATION_NUMBERS 20

#define VALID_YES_SIZE 2
#define VALID_NO_SIZE 2
#define VALID_OPERATIONS_SIZE 8
#define VALID_CHARACTERS_SIZE 12

#define DEFAULT_LOCALE "Portuguese" // Ao utilizar o locale o número de casas decimais do double é muito aproximado, então não foi usado

// Depois são definidas as estruturas dos arrays de entradas válidas do sistema
extern const char VALID_YES[VALID_YES_SIZE];

extern const char VALID_NO[VALID_NO_SIZE];

extern const char VALID_OPERATIONS[VALID_OPERATIONS_SIZE];

extern const char VALID_CHARACTERS[VALID_CHARACTERS_SIZE];
