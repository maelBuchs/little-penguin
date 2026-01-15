
#include <linux/usb.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/hid.h>

static const struct usb_device_id hell_key_table[] = {
	{	USB_INTERFACE_INFO(
			USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD)
	},
	{}
};



static int hell_key_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);

	printk(KERN_INFO "Hello, keyboard %s!\n", udev->product);
	return 0;
}



static void hell_key_disconnect(struct usb_interface *intf)
{
	printk(KERN_INFO "Cleaning up module.\n");
}


static struct usb_driver hello_keyboard_driver = {
	.name = "hello_keyboard",
	.probe = hell_key_probe,
	.id_table = hell_key_table,
	.disconnect = hell_key_disconnect,
};

static int __init hell_key_init(void){
	return usb_register(&hello_keyboard_driver);
}
static void __exit hell_key_exit(void){
	usb_deregister(&hello_keyboard_driver);
}

module_init(hell_key_init);
module_exit(hell_key_exit);

MODULE_DEVICE_TABLE(usb, hell_key_table);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ex04 : USB Keyboard Module");

