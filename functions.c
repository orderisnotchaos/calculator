#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


float (*operation_pointer[])(float,float)={add,subtract,multiply,divide,power};

float calculate( char *input ){

char buffer[MAX_DATA_SIZE];
char *numb=NULL;
float output,par_value;
int i,j,a,first_pos_controler;
Data *account=NULL;
Data *pivot=NULL;
i=0;
j=0;
a=0;

if ( isParOk(input) ){
	printf("syntax error\n");
	exit(1);
}


while( *(input+i)!='\0' ){

		if( account==NULL ){
			account= (Data *)malloc(sizeof(Data));
			if(account == NULL ){
				printf("memory allocation error\n");
				exit(1);
			}
			account->next=NULL;
			account->prev=NULL;
			pivot=account;

	        if( !(isoperator(*(input+i)) || isDigit(*(input+i)) ) ){
            	printf("syntax error\n");
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
				account->u.f=atof(numb);
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
					account->u.f=calculate(numb);
					free(numb);

				}else{
					account->u.c= *(input+i);
				}
			}

		}else{

			pivot->next=(Data *)malloc(sizeof(Data));
			if( pivot->next==NULL ){
				printf("memory allocation error\n");
				exit(1);
			}
			(pivot->next)->prev = pivot;
			(pivot->next)->next = NULL;
			pivot=pivot->next;


            if( !( isoperator(*(input+i)) || isDigit(*(input+i)) ) ){
                printf("syntax error\n");
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
		        pivot->u.f=atof(numb);
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
					pivot->u.f=calculate(numb);
					free(numb);
                }else{

					pivot->u.c = *(input+i);
				}
			}
		}

	i++;
}

pivot=account;
while( pivot!=NULL ){

	if(pivot->u.c==94){
		//power is executed
		first_pos_controler=operate(pivot,pivot->u.c);
		if(first_pos_controler){account=pivot;}
 	}

pivot=pivot->next;
}

pivot=account;
while( pivot!=NULL ){

	if(pivot->u.c=='*'|| pivot->u.c=='/'){

        if(pivot->u.c=='*'){
		//multiplication is produced
            first_pos_controler=operate(pivot,pivot->u.c);
			if(first_pos_controler){account=pivot;}
        }else{
		//division is produced
            first_pos_controler=operate(pivot,pivot->u.c);
			if(first_pos_controler){account=pivot;}
        }
	}
	pivot=pivot->next;
}

pivot=account;
while(pivot!=NULL){
		if(pivot->u.c=='+'||pivot->u.c=='-'){

			if(pivot->u.c=='+'){
			//adding is produced
				first_pos_controler=operate(pivot,pivot->u.c);
				if(first_pos_controler){account=pivot;}

			}else{
			//substraction is produced
				first_pos_controler=operate(pivot,pivot->u.c);
				if(first_pos_controler){account=pivot;}

			}
		}

pivot=pivot->next;
}
output=account->u.f;
return output;
}

int operate(Data *pivot,char operator){
	int i,first_pos_controler=0;
	Data *account;
	account=pivot;

	while( account->prev!=NULL ){
	account=account->prev;
	}

	switch(operator){
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
        pivot->u.f= (*operation_pointer[i])((pivot->prev)->u.f,(pivot->next)->u.f);
        if(pivot->prev==account){

			first_pos_controler=1;
		}

        pivot->prev=(pivot->prev)->prev;
        if(pivot->prev!=NULL){(pivot->prev)->next=pivot;}
        pivot->next=(pivot->next)->next;
        if(pivot->next!=NULL) {(pivot->next)->prev=pivot;}
return first_pos_controler;
}


