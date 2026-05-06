CC = gcc
CFLAGS = -Wall -I./include

TARGET = ./bin/scan

OBJ = ./obj/main.o ./obj/helper.o ./obj/output.o ./obj/scanner.o ./obj/input.o


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


./obj/main.o: ./src/main.c ./include/common.h ./include/helper.h ./include/scanner.h ./include/output.h ./include/input.h
	$(CC) $(CFLAGS) -c ./src/main.c -o ./obj/main.o

./obj/helper.o: ./src/helper.c ./include/helper.h
	$(CC) $(CFLAGS) -c ./src/helper.c -o ./obj/helper.o

./obj/scanner.o: ./src/scanner.c ./include/scanner.h
	$(CC) $(CFLAGS) -c ./src/scanner.c -o ./obj/scanner.o

./obj/output.o: ./src/output.c ./include/output.h
	$(CC) $(CFLAGS) -c ./src/output.c -o ./obj/output.o

./obj/input.o: ./src/input.c ./include/input.h ./include/helper.h ./include/scanner.h
	$(CC) $(CFLAGS) -c ./src/input.c -o ./obj/input.o


clean:
	rm -f ./obj/*.o ./bin/scan