#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("KIMRIHYEON");
MODULE_DESCRIPTION("GPIO device driver");
MODULE_VERSION("1.0");


/* Variables for device and device class */

#define GPIO_21 21

dev_t dev = 0;
static struct class *dev_class;
static struct cdev gpio_cdev;




static int gpio_open(struct inode *inode, struct file *file)
{
	pr_info("device open\n");
	return 0;
}

static int gpio_release(struct inode *inode, struct file *file)
{
	pr_info("device closed\n");
	return 0;
}

static ssize_t gpio_read(struct file *filp, char __user *buf,
			 size_t len, loff_t *off)
{
	uint8_t gpio_state = 0;

	gpio_state = gpio_get_value(GPIO_21);
	len = 1;

	if (copy_to_user(buf, &gpio_state, len) > 0)
		pr_err("error: copy to user \n");
  
	pr_info("gpio read: GPIO 21 pin = %d \n", gpio_state);

	return 0;
}

static ssize_t gpio_write(struct file *filp, const char __user *buf,
			  size_t len, loff_t *off)
{
	uint8_t rec_buf[10] = {0};
  
	if (copy_from_user(rec_buf, buf, len) > 0)
		pr_err("error: copy from user\n");
  
	pr_info("gpio write: GPIO 21 pin set = %c\n", rec_buf[0]);
  
	if (rec_buf[0]=='1')	
		gpio_set_value(GPIO_21, 1); //set the GPIO value to HIGH

	else if (rec_buf[0]=='0')
		gpio_set_value(GPIO_21, 0); //set the GPIO value to LOW
	else
		pr_err("unknown command\n");
  
	return len;
}

static struct file_operations fops =
{
	.owner          = THIS_MODULE,
	.read           = gpio_read,
	.write          = gpio_write,
	.open           = gpio_open,
	.release        = gpio_release,
};

static int __init gpio_driver_init(void)
{
	if((alloc_chrdev_region(&dev, 0, 1, "gpio_dev")) <0){
		pr_err("Error: cannot allocate major number\n");
		goto err_unreg;
	}
	pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
	cdev_init(&gpio_cdev,&fops);

	if((cdev_add(&gpio_cdev,dev,1)) < 0){
		pr_err("Error: annot add device \n");
		goto err_del;
	}

	if((dev_class = class_create(THIS_MODULE,"gpio_class")) == NULL){
		pr_err("Error: cannot create the struct class\n");
		goto err_class;
	}
 
	if((device_create(dev_class,NULL,dev,NULL,"gpio_device")) == NULL){
		pr_err( "Error: cannot create device \n");
		goto err_device;
	}

	if(gpio_is_valid(GPIO_21) == false){
		pr_err("GPIO %d is not valid\n", GPIO_21);
		goto err_device;
	}

	if(gpio_request(GPIO_21,"GPIO_21") < 0){
		pr_err("Error: GPIO %d request\n", GPIO_21);
		goto err_gpio;
	}

	gpio_direction_output(GPIO_21, 0);
	gpio_export(GPIO_21, false);

	pr_info("GPIO driver start\n");
	return 0;
 
err_gpio:
	gpio_free(GPIO_21);
err_device:
	device_destroy(dev_class,dev);
err_class:
	class_destroy(dev_class);
err_del:
	cdev_del(&gpio_cdev);
err_unreg:
	unregister_chrdev_region(dev,1);
  
	return -1;
}

static void __exit gpio_driver_exit(void)
{
	gpio_unexport(GPIO_21);
	gpio_free(GPIO_21);
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&gpio_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("GPIO driver done\n");
}
 
module_init(gpio_driver_init);
module_exit(gpio_driver_exit);





