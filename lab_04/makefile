CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wvla
OUT := ./out/
SRC := ./src/
INC := ./inc/
OBJ := $(OUT)arr_stack.o $(OUT)list_stack.o $(OUT)io.o $(OUT)reverse.o 

run : CFLAGS += -DNDEBUG -g0
run : app.exe

debug : CFLAGS += -g3
debug : app.exe

app.exe : $(OBJ) $(OUT)main.o
	$(CC) -o app.exe $(OBJ) $(OUT)main.o

$(OUT)main.o : $(SRC)main.c $(INC)common.h $(INC)arr_stack.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)main.c

$(OUT)arr_stack.o : $(SRC)arr_stack.c $(INC)arr_stack.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)arr_stack.c

$(OUT)list_stack.o : $(SRC)list_stack.c $(INC)list_stack.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)list_stack.c

$(OUT)io.o : $(SRC)io.c $(INC)io.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)io.c

$(OUT)reverse.o : $(SRC)reverse.c $(INC)reverse.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)reverse.c

.PHONY : clean debug release

clean :
	$(RM) $(OUT)*.o *.exe