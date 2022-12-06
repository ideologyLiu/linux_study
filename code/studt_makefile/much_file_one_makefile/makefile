FILE_ONE = file_one
FIlE_TWO = file_two

include ./file_one/SOURCE
include ./file_two/SOURCE


BIN_DIR = BIN
INC_DIR = -I ./file_one/ -I ./file_two/
SOURCE += $(wildcard *.c *.cpp)

printf.out:bin 
	gcc $(INC_DIR) $(SOURCE) -o $(BIN_DIR)/$@

bin:
	mkdir $(BIN_DIR)
		
clean:
	rm -rf $(BIN_DIR)
	
	
	