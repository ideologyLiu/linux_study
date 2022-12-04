include ./file_one/SOURCE
include ./file_two/SOURCE

L_FLAG = -I ./file_one/file_one.h -I ./file_two/file_two.h

all:printf.out
printf.out: file_one.o file_two.o
	@echo $(SOURCE)
	@echo $(L_FLAG)
	gcc main.o file_one.o file_two.o -o printf.out 
	
file_one.o:
	gcc -c ./file_one/file_one.c -o file_one.o
	
file_two.o:
	gcc -c ./file_two/file_two.c -o file_two.o
	
main.o:
	gcc -c ./main.c -o main.o
	
clean:
	rm -rf ./*.out
	rm -rf ./*.o