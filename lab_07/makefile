CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wvla
OUT := ./out/
SRC := ./src/
INC := ./inc/
OBJ := $(OUT)graph.o $(OUT)io.o $(OUT)karger.o $(OUT)set.o # $(OUT)effec.o

run : CFLAGS += -DNDEBUG -g0
run : app.exe

debug : CFLAGS += -g3
debug : app.exe

app.exe : $(OBJ) $(OUT)main.o
	$(CC) -o app.exe $(OBJ) $(OUT)main.o

$(OUT)main.o : $(SRC)main.c
	cd out && $(CC) $(CFLAGS) -c .$(SRC)main.c

$(OUT)io.o : $(SRC)io.c $(INC)io.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)io.c

$(OUT)karger.o : $(SRC)karger.c $(INC)karger.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)karger.c

$(OUT)set.o : $(SRC)set.c $(INC)set.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)set.c

$(OUT)graph.o : $(SRC)graph.c $(INC)graph.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)graph.c

$(OUT)effec.o : $(SRC)effec.c $(INC)effec.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)effec.c

.PHONY : clean debug release

clean :
	$(RM) $(OUT)*.o *.exe