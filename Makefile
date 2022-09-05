SRC= functions.c main.c operators.c
OBJS= prog 

all:$(SRC)

	gcc $(SRC) -o prog -lm

clean:
	 rm -r $(OBJS)
