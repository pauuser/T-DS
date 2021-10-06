CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wvla
OUT := ./out/
SRC := ./src/
OBJ := $(OUT)input.o $(OUT)operations.o $(OUT)output.o $(OUT)sort_key.o $(OUT)sort_table.o $(OUT)stats.o

run : CFLAGS += -DNDEBUG -g0
run : app.exe

debug : CFLAGS += -g3
debug : app.exe

app.exe : $(OBJ) $(OUT)main.o
	$(CC) -o app.exe $(OBJ) $(OUT)main.o

$(OUT)main.o : $(SRC)main.c $(SRC)common.h $(SRC)input.h $(SRC)operations.h $(SRC)output.h $(SRC)sort_key.h $(SRC)sort_table.h $(SRC)stats.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)main.c

$(OUT)input.o : $(SRC)input.c $(SRC)input.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)input.c

$(OUT)operations.o : $(SRC)operations.c $(SRC)operations.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)operations.c

$(OUT)output.o : $(SRC)output.c $(SRC)output.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)output.c

$(OUT)sort_key.o : $(SRC)sort_key.c $(SRC)sort_key.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)sort_key.c

$(OUT)sort_table.o : $(SRC)sort_table.c $(SRC)sort_table.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)sort_table.c

$(OUT)stats.o : $(SRC)stats.c $(SRC)stats.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)stats.c

.PHONY : clean debug release

clean :
	$(RM) $(OUT)*.o *.exe
