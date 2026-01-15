
obj-m += hello_keyboard.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	sudo mkdir -p /lib/modules/$(uname -r)/kernel/drivers/usb
	sudo cp hello_keyboard.ko /lib/modules/$(uname -r)/kernel/drivers/usb/

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

