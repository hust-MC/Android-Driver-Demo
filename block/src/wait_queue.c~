#include "../inc/wait_queue.h"

static ssize_t demo_read(struct file *file, char __user *buf, size_t count,
		loff_t *ppos)
{
	ssize_t result = 0;
		
	if (buffer_char_count > 0)
	{
		if (copy_to_user(buf, buffer, buffer_char_count))
		{
			return -EINVAL;
		}
		wake_up_interruptible(&my_queue);
		result = buffer_char_count;
		buffer_char_count = 0;
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
	wait_event_interruptible(my_queue, buffer_char_count == 0);
	if (copy_from_user(buffer, buf, count))
	{
		return -EINVAL;
	}
	result = count;
	buffer_char_count = result;
	return result;
}
static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = demo_read, .write = demo_write };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

//  初始化Linux驱动
static int __init demo_init(void)
{
	//  建立设备文件
	int ret = misc_register(&misc);

	init_waitqueue_head(&my_queue);

	print_debug("demo_init_success\n");

	return ret;
}

// 卸载Linux驱动
static void __exit demo_exit(void)
{
	print_debug("demo_exit_success\n");
	//  删除设备文件
	misc_deregister(&misc);
}
//  注册初始化Linux驱动的函数
module_init( demo_init);
//  注册卸载Linux驱动的函数
module_exit( demo_exit);
MODULE_LICENSE("GPL");
