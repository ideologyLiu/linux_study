include ./file_one/SOURCE
include ./file_two/SOURCE


BIN_DIR = BIN
INC_DIR = -I ./file_one/ -I ./file_two/
SOURCE += main.c

OBJS=$(patsubst %.c, %.o, $(SOURCE))

%.o:%.c
	gcc -c $(INC_DIR) -o $@ -c $^

printf.out:bin $(OBJS)
	gcc $(OBJS) -o $(BIN_DIR)/$@
bin:
	mkdir $(BIN_DIR)
	
	
clean:
	rm -rf $(OBJS)
	rm -rf $(BIN_DIR)
	
	
	