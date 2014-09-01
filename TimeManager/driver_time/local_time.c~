#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>

static int __init demo_init(void)
{
	struct timeval tv;
	struct timespec ts;

	ts.tv_nsec = 0;		//设置纳秒时间
	ts.tv_sec = (unsigned long)mktime(2012,9,23,16,11,23);		//设置修改的时间

	do_gettimeofday(&tv);
	printk("sec:%ld,usec:%ld\n",tv.tv_sec,tv.tv_usec);
		
	do_settimeofday(&ts);
	printk("set success!\n");
	printk("init success");	
	return 0;
}

static void __exit demo_exit(void)
{
	printk("exit");
} 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MC");
module_init(demo_init);
module_exit(demo_exit);
