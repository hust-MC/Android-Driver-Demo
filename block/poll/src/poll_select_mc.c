#include "../inc/poll_select.h"

static ssize_t demo_read(struct file *file, char __user *buf, size_t count,
		loff_t *ppos)
{
	ssize_t result = 0;

printk("read\n");
	if (buffer_char_count > 0)
	{
		if(down_interruptible(&sem))
			return -ERESTARTSYS;
		if (copy_to_user(buf, buffer, buffer_char_count))
		{
			return -EINVAL;
		}

		wake_up_interruptible(&my_queue);
		result = buffer_char_count;
		buffer_char_count = 0;
		up(&sem);
printk("result = %d\n",result);
printk("count = %d\n",count);
		return result;
	}
	else
	{
		return 0;
	}


	return result;
}

static ssize_t demo_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	ssize_t result = 0;
	if(down_interruptible(&sem))
		return -ERESTARTSYS;
	wait_event_interruptible(my_queue, buffer_char_count == 0);
	if (copy_from_user(buffer, buf, count))
	{
		return -EINVAL;
	}
	result = count;
	buffer_char_count = count;
	up(&sem);
	return result;
}
unsigned int demo_poll(struct file *filp, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	if(down_interruptible(&sem))
		return -ERESTARTSYS;

	poll_wait(filp, &my_queue, wait);
	// read
	if(buffer_char_count > 0)
	{
		mask |= POLLIN | POLLRDNORM;
	}
	//  write
	if(buffer_char_count == 0)
	{
		mask |= POLLOUT | POLLWRNORM;
	}
	up(&sem);
    return mask;
}
static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = demo_read, .write = demo_write, .poll=demo_poll };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

//  初始化Linux驱动
static int __init demo_init(void)
{

	//  建立设备文件
	int ret = misc_register(&misc);
	init_waitqueue_head(&my_queue);
	sema_init(&sem, 1);
	printk("demo_init_success\n");

	return ret;
}

// 卸载Linux驱动
static void __exit demo_exit(void)
{
	printk("demo_exit_success\n");
	//  删除设备文件
	misc_deregister(&misc);
}
//  注册初始化Linux驱动的函数
module_init( demo_init);
//  注册卸载Linux驱动的函数
module_exit( demo_exit);
MODULE_LICENSE("GPL");
