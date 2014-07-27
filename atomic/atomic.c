#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

#include <asm/uaccess.h>
#include <asm/atomic.h>

//定义设备文件名
#define	DEVICE_NAME "atomic"

/**驱动层参数变量
*  0:关闭原子操作控制，多个进程可以同时打开设备文件
*  非0：打开原子操作控制
*/
static int atom = 0;
static int atomic_t int_atomic_availabel = ATOMIC_INIT(1);

static struct file_operations dev_fops =
{
		.owner = THIS_MODULE,
		.open = atomic_open,
		.release = atomic_release
};

static struct miscdevice misc =
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &dev_fops
};

static int atomic_init(void)
{
	int ret = misc_register(&misc);
}





module_init(atomic_init);
module_exit(atomic_exit);
