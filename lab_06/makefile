CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wvla
OUT := ./out/
SRC := ./src/
INC := ./inc/
OBJ := $(OUT)bst.o $(OUT)graph.o $(OUT)io.o # $(OUT)avl.o

run : CFLAGS += -DNDEBUG -g0
run : app.exe

debug : CFLAGS += -g3
debug : app.exe

app.exe : $(OBJ) $(OUT)main.o
	$(CC) -o app.exe $(OBJ) $(OUT)main.o

$(OUT)main.o : $(SRC)main.c
	cd out && $(CC) $(CFLAGS) -c .$(SRC)main.c

$(OUT)bst.o : $(SRC)bst.c $(INC)bst.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)bst.c

#$(OUT)avl.o : $(SRC)avl.c $(INC)avl.h
#	cd out && $(CC) $(CFLAGS) -c .$(SRC)avl.c

$(OUT)graph.o : $(SRC)graph.c $(INC)graph.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)graph.c

$(OUT)io.o : $(SRC)io.c $(INC)io.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)io.c

.PHONY : clean debug release

clean :
	$(RM) $(OUT)*.o *.exe