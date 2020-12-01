obj-m := hello.o

KERNELDIR = /usr/src/linux-headers-5.4.0-52-generic/
#KERNELDIR = /lib/module/$(shell uname -r)/build/

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

#install:
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean    