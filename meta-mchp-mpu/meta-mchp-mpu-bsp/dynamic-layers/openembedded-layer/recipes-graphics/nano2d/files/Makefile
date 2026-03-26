SRC := $(shell pwd)/git/drv/nano2Dkernel

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

clean:
	cd $(SRC); \
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c; \
	rm -f Module.markers Module.symvers modules.order; \
	rm -rf .tmp_versions Modules.symvers
