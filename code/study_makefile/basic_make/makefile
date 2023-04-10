target = $(patsubst %.c,%,$(wildcard *.c))

ALL:$(target)

%:%.c
	gcc $< -o $@ 

clean:
	rm -rf $(target)

.PHONY:clean ALL