CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wvla
OUT := ./out/
SRC := ./src/
INC := ./inc/
OBJ := $(OUT)arr_queue.o $(OUT)time_func.o #$(OUT)list_queue.o

run : CFLAGS += -DNDEBUG -g0
run : app.exe

debug : CFLAGS += -g3
debug : app.exe

app.exe : $(OBJ) $(OUT)main.o
	$(CC) -o app.exe $(OBJ) $(OUT)main.o

$(OUT)main.o : $(SRC)main.c
	cd out && $(CC) $(CFLAGS) -c .$(SRC)main.c

$(OUT)arr_queue.o : $(SRC)arr_queue.c $(INC)arr_queue.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)arr_queue.c

#$(OUT)list_queue.o : $(SRC)list_queue.c $(INC)list_queue.h
#	cd out && $(CC) $(CFLAGS) -c .$(SRC)list_queue.c

$(OUT)time_func.o : $(SRC)time_func.c $(INC)time_func.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)time_func.c

.PHONY : clean debug release

clean :
	$(RM) $(OUT)*.o *.exe