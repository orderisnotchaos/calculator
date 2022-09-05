#include <stdio.h>
#define MAX_DATA_SIZE 256
#define MAX_NUMB_SIZE 15
#define ERR_SINTAX "sintax error.\n"
#define HELP_SINTAX "the count must end with the char =.\n"
#define PRINT_VALUE "the %d value is: %.2f.\n"



typedef union{
	float f;
	char c;
}Union;

typedef struct node{
	Union u;
	struct node *next;
	struct node *prev;
}Data;

char getC(void);

int isDigit(int);

float add(float,float);

float subtract(float,float);

float multiply(float,float);

float divide(float,float);

float power(float,float);

float calculate(char *);

int isParOk(char *);

int isSimbOk(char *);

int isoperator(int);

int isValid(char *);

void list(Data *);

char *fixedGets(char *,FILE *);

int operate(Data *, char);
