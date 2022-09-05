#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc,char **argv){
char buffer[MAX_DATA_SIZE];
float r;
char a='\0';
int n=1;
FILE *f,*s;
if(argv[1]==NULL){
	printf("======================\n");
	printf("Welcome to the recursive calculator\n");
	printf("======================\n\n");
	printf("if you wish to pass the accounts via file execute ./prog [your_file]\n");

	printf("write what you wish to calculate:\n");
	fixedGets(buffer,stdin);
	r=calculate(buffer);
	printf("your result: %.2f\n",r);
	while(1){
		printf("Do you wish to calculate something else? press y/n\n");
		a=getC();
		if(a=='n') break;
		printf("write what you wish to calculate: \n");
		fixedGets(buffer,stdin);
	        r=calculate(buffer);
		printf("your result: %.2f\n",r);

	}

}else{

	f=fopen(argv[1],"r");
	s=fopen("data_out","ab");

	if(f==NULL){
		printf("invalid address.\n");
		fclose(f);
		exit(1);
	}

	while( fixedGets(buffer,f)!=NULL ){

		if( buffer!=NULL ){
			r=calculate(buffer);
			fprintf(s,"%d° result: %.2f\n",n,r);
			printf(PRINT_VALUE,n,r);
			n++;
		}else{
			printf(ERR_SINTAX);
			printf(HELP_SINTAX);
		}
	}
fclose(f);
fclose(s);
}
return 0;
}

