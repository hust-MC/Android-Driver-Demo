#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <asm/uaccess.h>

#include <mach/regs-gpio.h>
#include <mach/gpio.h>

#include <mach/map.h>

#define DEVIECE_NAME	"tiny210_leds"		//设备名称
#define DEVICE_COUNT	1					//设备文件数量
#define tiny210_LEDS_MAJOR	0				//默认主设备号
#define tiny210_LEDS_MINOR	234				//默认次设备号
#define PARAM_SIZE	3						//定义数组模块参数大小

static int major = tiny210_LEDS_MAJOR;		//主设备号
static int minor = tiny210_LEDS_MINOR;		//次设备号
static dev_t dev_number;					//设备号
static char *params[] = { "string1", "string2", "string3" };
static int leds_state = 1;
static int param_size = PARAM_SIZE;
static struct class *leds_class = NULL;							//创建class
static struct cdev leds_cdev;									//设备描述

static int led_gpios[] = { S5PV210_GPJ2(0), S5PV210_GPJ2(1), S5PV210_GPJ2(2),
		S5PV210_GPJ2(3), };										//LED的引脚值

static ssize_t word_count_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	
	if ((copy_from_user(tmp, buf, n)))
	{
		return -EFAULT;
	}
	
	return count;
}

static long leds_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	if (cmd == 1 || cmd == 0)
	{
		if (arg > 4)
		{
			return -EINVAL;
		}
	} else
	{
		return -EINVAL;
	}
	return 0;
}

static struct file_operations dev_fops = { .owner = THIS_MODULE, .write =
		word_count_write, .unlocked_ioctl = leds_ioctl };		//设置fops

static int leds_create_device(void)
{
	int ret = 0;
	int err = 0;
//1.初始化cdev的成员，建立cdev和fops之间的连接
	cdev_init(&leds_cdev, &dev_fops);
	leds_cdev.owner = THIS_MODULE;

//2.主设备号大于0，通过指定设备号注册字符设备区域
	if (major > 0)
	{
		dev_number = MKDEV(major, minor);
		err = register_chrdev_region(dev_number, DEVICE_COUNT, DEVIECE_NAME);
		if (err < 0)
		{
			printk(KERN_WARNING "register_chrdev_region failed\n");
			return err;
		}
	} else  //主设备号为0，随即分配设备号这册字符设备区域
	{
		err = alloc_chrdev_region(&leds_cdev.dev, 10, DEVICE_COUNT,
		DEVIECE_NAME);
		if (err < 0)
		{
			printk("alloc_chrdev_region failed\n");
			return err;
		}

		major = MAJOR(leds_cdev.dev);
		minor = MINOR(leds_cdev.dev);
		dev_number = leds_cdev.dev;
	}
//3.将字符设备添加到内核中的字符数组中
	ret = cdev_add(&leds_cdev, leds_cdev.dev, DEVICE_COUNT);
//4.创建struct class
	leds_class = class_create(THIS_MODULE, DEVIECE_NAME);
//5.创建设备文件
	device_create(leds_class, NULL, dev_number, NULL, DEVIECE_NAME);
	return ret;
}

static void leds_destroy_device(void)
{
	device_destroy(leds_class, dev_number);			//移除通过device_create创建的字符设备
	if (leds_class)
	{
		class_destroy(leds_class);                  //销毁通过class_create创建的class
	}
	unregister_chrdev_region(dev_number, DEVICE_COUNT);	//销毁通过register/alloc_chrdev_region创建的字符设备区域
	return;
}

static int leds_init(void)
{
	int ret, i;
//创建设备文件
	ret = leds_create_device();
	printk(DEVIECE_NAME"\tinitialized\n");
	for (i = 0; i < 4; i++)
	{
		gpio_set_value(led_gpios[i], ~leds_state);
	}
	
	return ret;
}

static void leds_exit(void)
{
	leds_destroy_device();
	printk(DEVIECE_NAME"\texit\n");
}

module_init(leds_init);
module_exit(leds_exit);
module_param(leds_state, int type, S_IRUGO| S_IWUSR);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MC");
