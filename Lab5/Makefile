ifneq ($(KERNELRELEASE),)

obj-m := hello1.o hello2.o

ccflags-y += -I$(src)/inc

else
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif
