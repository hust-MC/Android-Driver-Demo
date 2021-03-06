#include "../inc/rw_lock.h"
//  定义设备文件名
#define DEVICE_NAME "rw_lock"
  
static char *data = "read\n";
static DEFINE_RWLOCK(rwlock);
static DEFINE_SPINLOCK(lock);

static char *lock_type = "rw";
static ssize_t demo_read(struct file *file, char __user *buf, size_t count,
        loff_t *ppos)
{

	int size = strlen(data);
	struct timeval tv;
	if (copy_to_user(buf, (void*) data, size))
	{
		return -EINVAL;
	}
	do_gettimeofday(&tv);
	printk("read:start sec:%ld\n", tv.tv_sec);
	if (strcmp(lock_type, "rw") == 0)
	{
		read_lock(&rwlock);
	}
	else if (strcmp(lock_type, "spin") == 0)
	{
		spin_lock(&lock);
	}
	do_gettimeofday(&tv);
	printk("read:end sec:%ld\n", tv.tv_sec);
	mdelay(5000);
	if (strcmp(lock_type, "rw") == 0)
	{
		read_unlock(&rwlock);
	}
	else if (strcmp(lock_type, "spin") == 0)
	{
		spin_unlock(&lock);
	}

	return size;

}

static ssize_t demo_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{
	struct timeval tv;
	do_gettimeofday(&tv);
	printk("write:start sec:%ld\n", tv.tv_sec);
	if (strcmp(lock_type, "rw") == 0)
	{
		write_lock(&rwlock);
	}
	else if (strcmp(lock_type, "spin") == 0)
	{
		spin_lock(&lock);
	}

	do_gettimeofday(&tv);
	printk("write:end sec:%ld\n", tv.tv_sec);
        mdelay(5000);
	if (strcmp(lock_type, "rw") == 0)
	{
		write_unlock(&rwlock);
	}
	else if (strcmp(lock_type, "spin") == 0)
	{
		spin_unlock(&lock);
	}


	return count;
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

module_param(lock_type, charp, S_IRUGO|S_IWUSR);

MODULE_LICENSE("GPL");
