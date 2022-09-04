SRC= funciones.c main.c operadores.c
OBJS= prog 

all:$(SRC)

	gcc $(SRC) -o prog -lm

clean:
	 rm -r $(OBJS)
