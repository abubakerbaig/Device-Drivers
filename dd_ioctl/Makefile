obj-m := ioctl.o

KERDIR = /lib/modules/$(shell uname -r)/build/
PWD = $(shell pwd)

default:
	$(MAKE) -C $(KERDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERDIR) M=$(PWD) clean