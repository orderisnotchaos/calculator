#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main(int argc,char **argv){
char buffer[MAX_DATA_SIZE];
float r;
char a='\0';
int n=1;
FILE *f,*s;
if(argv[1]==NULL){
	printf("======================\n");
	printf("Bienvenido a la calculadora recursiva\n");
	printf("======================\n\n");
	printf("si desea pasar las cuentas por archivo ejecute ./prog [su_archivo]\n");

	printf("escriba lo que desee calcular:\n");
	fixedGets(buffer,stdin);
	r=calcular(buffer);
	printf("su resultado: %.2f\n",r);
	while(1){
		printf("¿Desea hacer otra cuenta? presione s/n\n");
		a=getC();
		if(a=='n') break;
		printf("escriba lo que desee calcular: \n");
		fixedGets(buffer,stdin);
	        r=calcular(buffer);
		printf("su resultado: %.2f\n",r);

	}

}else{
//	puts("asdad");
	f=fopen(argv[1],"r");
	s=fopen("data_out","ab");

	if(f==NULL){
		printf("dirección inválida.\n");
		fclose(f);
		exit(1);
	}

//	puts("asdasd");
	while( fixedGets(buffer,f)!=NULL ){

		if( buffer!=NULL ){
			r=calcular(buffer);
			fprintf(s,"%d° resultado: %.2f\n",n,r);
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

