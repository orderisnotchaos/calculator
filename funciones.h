#include <stdio.h>
#define MAX_DATA_SIZE 256
#define MAX_NUMB_SIZE 15
#define ERR_SINTAX "sintax error.\n"
#define HELP_SINTAX "la cuenta debe terminar con el símbolo =.\n"
#define PRINT_VALUE "el %d valor es: %.2f.\n"



typedef union{
	float f;
	char c;
}Union;

typedef struct nodo{
	Union u;
	struct nodo *sig;
	struct nodo *ant;
}Dato;

char getC(void);

int isDigit(int);

float sumar(float,float);

float restar(float,float);

float multiplicar(float,float);

float dividir(float,float);

float potencia(float,float);

float calcular(char *);

int isParOk(char *);

int isSimbOk(char *);

int isoperator(int);

int isValid(char *);

void listar(Dato *);

char *fixedGets(char *,FILE *);

int operar(Dato *, char);
