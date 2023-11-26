target = $(patsubst %.c,%,$(wildcard *.c))

ALL:$(target)

%:%.c
	$(CC) $< -o $@ -lpthread -lrt 

clean:
	rm -rf $(target)

.PHONY:clean ALL