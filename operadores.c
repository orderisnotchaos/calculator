#include "funciones.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void listar(Dato *lista){
int i=0;
while( lista!=NULL ){
printf("subciclo número: %d\n",i);
printf("%.2f\n",lista->u.f);
printf("%c\n",lista->u.c);
lista=lista->sig;
i++;
}

}


char *fixedGets(char *buffer,FILE *f){
int i=0;
char *r;
	r=fgets(buffer,MAX_DATA_SIZE,f);
	while(*(buffer+i)!='\0'){
		if(*(buffer+i)=='\n'){
			*(buffer+i)='\0';
			break;
		}
		i++;
	}

return r;
}

float sumar(float a,float b){

return a+b;
}
float potencia(float a,float b){

return pow(a,b);
}
float restar(float a,float b){

return a-b;
}
float multiplicar(float a,float b){

return a*b;
}
float dividir(float a,float b){

return a/b;
}
int isParOk(char *input){
int a,i;
        for( i=0,a=0;*(input+i)!='\0' && a>=0;i++ ){
                if(*(input+i)=='('){a++;}
		if(*(input+i)==')'){a--;}
        }
return a;
}
/*int isfloat(int c){
if(isdigit(c) || c == '.') {return 1;}
else {return 0;}

}
*/
int isoperator(int c){
switch (c){
        case '/':
        break;
        case'*':
        break;
        case'+':
        break;
        case'-':
        break;
        case'(':
        break;
        case')':
        break;
        case 94:
        break;
        default:
        return 0;
        break;
        }
return c;
}

int isDigit(int c){

if(isdigit(c)) return 1;
else if(c=='.') return 1;
else return 0;
}
/*

int isValid(char *input){
        if(isSimbOk(input)){
                return 1;
        }
        else{
                return 0;
        }
}

int isSimbOk(char *input){
int i=0;
int j=0;
        while( *(input+i)!='\0' ){
                if(isoperator(*(input+i+1)) && *(input+i+1)!=('('||')') || *(input+i+1)=='='){
                        j++;
                }
        i++;
        }

printf("isSImbOk returned %d\n",j);
return j;
}
*/
char getC(void){
char c;
char buffer[MAX_DATA_SIZE];
        while(1){
                fixedGets(buffer,stdin);

                if(strlen(buffer)>1){
                        printf("ingrese una sola letra\n");
			continue;
                }
                c= *buffer;
                if( c!='s' && c!='n' ){
                        printf("opción inválida.\n");
                }else{
                        break;
                }
        }
return c;
}





