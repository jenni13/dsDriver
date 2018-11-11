TARGET_MODULE = ds18b20

ifneq ($(KERNELRELEASE),)
	obj-m := ds18b20.o
	util-objs := utils.o
else
	KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C ${KERNEL_DIR} M=$(PWD) modules

clean:
	rm $(TARGET_MODULE).ko
	rm $(TARGET_MODULE).mod.c
	rm *.o
	rm modules.order
	rm -f Module.symvers

endif
