include ./file_one/SOURCE
include ./file_two/SOURCE

OBJ_DIR = OBJ
BIN_DIR = BIN
L_FLAG = -I ./file_one/file_one.h -I ./file_two/file_two.h

all:printf.out
printf.out:OBJ_DIR file_one.o file_two.o main.o
	@echo $(SOURCE)
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/file_one.o $(OBJ_DIR)/file_two.o -o $(BIN_DIR)/printf.out 
	
file_one.o:
	gcc -c ./file_one/file_one.c -o $(OBJ_DIR)/file_one.o
	
file_two.o:
	gcc -c ./file_two/file_two.c -o $(OBJ_DIR)/file_two.o
	
main.o:
	gcc -c main.c -o $(OBJ_DIR)/main.o
	
OBJ_DIR:
	mkdir $(OBJ_DIR)
	mkdir $(BIN_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)