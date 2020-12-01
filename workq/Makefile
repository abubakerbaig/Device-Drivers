obj-m+=sample.o

KERN_SRC=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

modules:
	$(MAKE) -C $(KERN_SRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERN_SRC) M=$(PWD) clean