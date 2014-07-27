#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/types.h>

#include <asm/uaccess.h>
#include <asm/atomic.h>

#include "../inc/atomic_demo.h"
//定义设备文件名
#define	DEVICE_NAME "atomic"

/**驱动层参数变量
 *  0:关闭原子操作控制，多个进程可以同时打开设备文件
 *  非0：打开原子操作控制
 */
static int atom = 0;
static atomic_t int_atomic_available = ATOMIC_INIT(1);

static int atomic_open(struct inode *node, struct file *file)
{
	if(atom)
	{
		//先将int_atomic_available的值减1，然后判断int_atomic_available变量的值，如果不为0，则已被打开
		if(!atomic_dec_and_test(&int_atomic_available))
		{
			atomic_inc(&int_atomic_available);
		}
		return -EBUSY;
	}
	return 0;
}

static void atomic_release(struct inode *node, struct file *file)
{
	if(atom)
	{
		atomic_inc(&int_atomic_available);
	}
	return 0;
}

static struct file_operations dev_fops = { .owner = THIS_MODULE, .open =
		atomic_open, .release = atomic_release };

static struct miscdevice misc = { .minor = MISC_DYNAMIC_MINOR, .name =
		DEVICE_NAME, .fops = &dev_fops };

static int atomic_init(void)
{
	int ret = misc_register(&misc);
	print_debug("atomic_init_success\n");
	return ret;
}

static void atomic_exit(void)
{
	print_debug("atomic_exit_success\n");
	misc_deregister(&misc);
}


module_init(atomic_init);
module_exit(atomic_exit);

module_param(atom, int, S_IRUGO|S_IWUSR);

MODULE_LICENSE("GPL");
