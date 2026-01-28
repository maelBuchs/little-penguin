#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h> 

#define LOGIN "mbuchs"
#define LOGIN_SIZE 6

static ssize_t ft_read(struct file *filp, char __user *ubuf, size_t count, loff_t *off);
static ssize_t ft_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *off);

struct file_operations ft_fops = {
	.read = ft_read,
	.write = ft_write
};

static struct miscdevice ft_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fortytwo",
	.mode = 0666,
	.fops = &ft_fops
};



static int __init ftdrv_init(void)
{
	printk(KERN_INFO "Init /dev/fortytwo device driver\n");

	int ret;
	struct device *dev;

	ret = misc_register(&ft_dev);
	if (ret !=0){
		pr_notice("misc device registration failed, aborting\n");
		return ret;
	}
	dev = ft_dev.this_device;
	pr_info("ft_driver (major # 10), minor # %d,\n dev node is /dev/%s\n",ft_dev.minor, ft_dev.name);
	dev_info(dev, "sample dev_info(): minor # %d\n", ft_dev.minor);
	return 0;
}

static ssize_t ft_read(struct file *filp, char __user *ubuf, size_t count, loff_t *off)
{
	char buffer[LOGIN_SIZE + 2] = {"mbuchs\n"} ;
	return simple_read_from_buffer(ubuf, count, off, buffer, strlen(buffer));
}

static ssize_t ft_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *off){
	char buffer[LOGIN_SIZE + 2];
	
	if(count != LOGIN_SIZE && count != LOGIN_SIZE + 1)
	{
		pr_err("invalid size\n");
		return -EINVAL;
	}
	if (copy_from_user(buffer, ubuf, count))
		return -EFAULT;
	if (count == 7 && buffer[LOGIN_SIZE] && buffer[LOGIN_SIZE] != '\n')
		return -EINVAL;
	buffer[LOGIN_SIZE] = 0;
	if (strcmp(LOGIN, buffer))
	{	
		pr_err("invalid content\n");
		return -EINVAL;
	}
	return count;
}

static void __exit ftdrv_exit(void)
{
	misc_deregister(&ft_dev);
	printk(KERN_INFO "Cleaning up module.\n");
}

module_init(ftdrv_init);
module_exit(ftdrv_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ex05 : Misc Char");

