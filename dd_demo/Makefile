obj-m+= cdriver.o

KERNELDIR = /lib/modules/5.4.0-52-generic/build/
#KERNELDIR = /usr/src/linux-headers-5.4.0-52-generic/

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean