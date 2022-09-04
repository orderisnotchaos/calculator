#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


float (*puntero_operacion[])(float,float)={sumar,restar,multiplicar,dividir,potencia};

float calcular( char *input ){

char buffer[MAX_DATA_SIZE];
char *numb=NULL;
float output,par_value;
int i,j,a,first_pos_controler;
Dato *cuenta=NULL;
Dato *pivote=NULL;
i=0;
j=0;
a=0;

if ( isParOk(input) ){
	printf("syntax error\n");
	exit(1);
}


while( *(input+i)!='\0' ){

		if( cuenta==NULL ){
			cuenta= (Dato *)malloc(sizeof(Dato));
			if(cuenta == NULL ){
				printf("memory allocation error\n");
				exit(1);
			}
			cuenta->sig=NULL;
			cuenta->ant=NULL;
			pivote=cuenta;

	        if( !(isoperator(*(input+i)) || isDigit(*(input+i)) ) ){
            	printf("sintaxis incorrecta\n");
                exit(1);
            }


			if( isDigit(*(input+i)) ){
				j=0;
				numb = (char *)malloc(sizeof(char)*MAX_NUMB_SIZE);
				while( isDigit(*(input+i+j)) && (i+j)<=strlen(input) ){
					*(numb+j)= *(input+i+j);
					j++;
				}

				i+=j-1;
				cuenta->u.f=atof(numb);
				free(numb);
			}

			if( isoperator(*(input+i)) ){
				if(*(input+i)=='('){
					i++;
	        	    a=1;
		            j=0;
					numb=(char *)malloc(sizeof(char)*MAX_DATA_SIZE);
					if( numb==NULL ){
						printf("memory allocation error\n");
						exit(1);
					}
		            while(a!=0){
		                if(*(input+i+j)=='('){a++;}
		                if(*(input+i+j)==')'){a--;}
						if(a==0){ *(numb+j)='\0';}
						else{ *(numb+j)= *(input+i+j);}
		                j++;
                    }
					i+=j-1;
					cuenta->u.f=calcular(numb);
					free(numb);

				}else{
					cuenta->u.c= *(input+i);
				}
			}

		}else{

			pivote->sig=(Dato *)malloc(sizeof(Dato));
			if( pivote->sig==NULL ){
				printf("memory allocation error\n");
				exit(1);
			}
			(pivote->sig)->ant = pivote;
			(pivote->sig)->sig = NULL;
			pivote=pivote->sig;


            if( !( isoperator(*(input+i)) || isDigit(*(input+i)) ) ){
                printf("sintaxis incorrecta\n");
                exit(1);
            }

	        if( isDigit(*(input+i)) ){

				j=0;
				numb=(char *)malloc(sizeof(char)*MAX_NUMB_SIZE);

		      	while( isDigit(*(input+i+j)) && i+j<=strlen(input) ){
		            *(numb+j)= *(input+i+j);
        		    j++;
		        }
				i+=j-1;
		        pivote->u.f=atof(numb);
				free(numb);
			}

			if( isoperator(*(input+i)) ){
                if( *(input+i)=='(' ){
					i++;
                    a=1;
                    j=0;
                    numb=(char *)malloc(sizeof(char)*MAX_DATA_SIZE);
                    while(a!=0){


                        if(*(input+i+j)=='('){a++;}
                        if(*(input+i+j)==')'){a--;}
						if(a==0){*(numb+j)='\0';}
                        else{*(numb+j)= *(input+i+j);}
                        j++;
                    }
					i+=j-1;
					pivote->u.f=calcular(numb);
					free(numb);
                }else{

					pivote->u.c = *(input+i);
				}
			}
		}

	i++;
}

pivote=cuenta;
while( pivote!=NULL ){

	if(pivote->u.c==94){
		//se efectua la potenciación
		first_pos_controler=operar(pivote,pivote->u.c);
		if(first_pos_controler){cuenta=pivote;}
 	}

pivote=pivote->sig;
}
pivote=cuenta;
while( pivote!=NULL ){

	if(pivote->u.c=='*'|| pivote->u.c=='/'){

        if(pivote->u.c=='*'){
		//se efectua la multiplicacion
            first_pos_controler=operar(pivote,pivote->u.c);
			if(first_pos_controler){cuenta=pivote;}
        }else{
		//se efectua la division
            first_pos_controler=operar(pivote,pivote->u.c);
			if(first_pos_controler){cuenta=pivote;}
        }

	}

pivote=pivote->sig;
}

pivote=cuenta;

while(pivote!=NULL){
		if(pivote->u.c=='+'||pivote->u.c=='-'){

			if(pivote->u.c=='+'){
			//se efectua la suma
				first_pos_controler=operar(pivote,pivote->u.c);
				if(first_pos_controler){cuenta=pivote;}

			}else{
			//se efectua la resta
				first_pos_controler=operar(pivote,pivote->u.c);
				if(first_pos_controler){cuenta=pivote;}

			}
		}

pivote=pivote->sig;
}
output=cuenta->u.f;
return output;
}

int operar(Dato *pivote,char operador){
int i,first_pos_controler=0;
Dato *cuenta;
cuenta=pivote;

while( cuenta->ant!=NULL ){
cuenta=cuenta->ant;
}
//printf("%f\n",cuenta->u.f);

	switch(operador){
		case 94:
			 i=4;
			break;
		case 42:
			i=2;
			break;
		case 43:
			i=0;
			break;
		case 45:
			i=1;
			break;
		case 47:
			i=3;
			break;
	}
        pivote->u.f= (*puntero_operacion[i])((pivote->ant)->u.f,(pivote->sig)->u.f);
        if(pivote->ant==cuenta){
			cuenta=pivote;
			first_pos_controler=1;
		}
        pivote->ant=(pivote->ant)->ant;
        if(pivote->ant!=NULL){(pivote->ant)->sig=pivote;}
        pivote->sig=(pivote->sig)->sig;
        if(pivote->sig!=NULL) {(pivote->sig)->ant=pivote;}
return first_pos_controler;
}


