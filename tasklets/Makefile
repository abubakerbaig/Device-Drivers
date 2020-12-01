obj-m := tasklets.o

KD = /lib/modules/$(shell uname -r)/build/
PWD=$(shell pwd)

default:
	$(MAKE) -C $(KD) M=$(PWD) modules
clean:
	$(MAKE) -C $(KD) M=$(PWD) clean