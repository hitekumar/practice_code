obj-m+=simplechardev.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) test_simplechardev.c -o test_simplechardev
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm test_simplechardev
