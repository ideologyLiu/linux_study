FILE_ONE = file_one
FIlE_TWO = file_two

include ./file_one/SOURCE
include ./file_two/SOURCE


BIN_DIR = BIN
OBJ_DIR = OBJ
SOURCE += $(wildcard *.c *.cpp)

OBJS=$(patsubst %.c, %.o, $(SOURCE))

%.o:%.c
	gcc -c -o $@  $^

printf.out:dir $(OBJS) mv
	gcc $(wildcard $(OBJ_DIR)/*.o) -o $(BIN_DIR)/$@

dir:
	mkdir $(BIN_DIR)
	mkdir $(OBJ_DIR)
	
mv:
	mv $(OBJS) $(OBJ_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	
	
	
	