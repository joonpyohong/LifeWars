

CC = clang
CFLAGS = -Wall -Wextra -pedantic -Wfloat-equal -std=c90
LIBS = -lm
SRC_PATH = ./src/
INCLUDE_PATH = -I./include/
SOURCE = $(SRC_PATH)lifewar.c $(SRC_PATH)gameLogic.c $(SRC_PATH)board.c
EXECUTABLE = .\bin\lifewar.exe

LIF_FILE_1 = .\lif\goosegun.lif
LIF_FILE_2 = .\lif\sawtooth.lif

build: $(SOURCE)
	$(CC) $(SOURCE) -o $(EXECUTABLE) $(CFLAGS) $(INCLUDE_PATH) $(LIBS)

run: $(EXECUTABLE)
	$(EXECUTABLE) $(LIF_FILE_1) $(LIF_FILE_2)

clean:
	del $(EXECUTABLE)

