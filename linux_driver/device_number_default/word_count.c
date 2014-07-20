#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

#define DEVICE_NAME "wordcount1"
#define TRUE  1
#define FALSE 0
static unsigned char mem[10000];
static char read_flag = 'y';
static int word_count = 0;
static int ret;


static ssize_t word_count_read(struct file *file, char __user *buf, size_t count , loff_t *ppos)
{
 

    copy_to_user(buf, (void*) temp, 4);

  
    return word_count;
}

static ssize_t word_count_write(struct file *file, const char __user *buf, size_t count , loff_t *ppos)
{
    copy_from_user(mem, buf, count);
   
    return count;
}

//owner表示设备事件回调函数应用于拿些驱动模块; THIS_MODULE表示应用于当前驱动模块
static struct file_operations dev_fops =
{
    .owner = THIS_MODULE, .read = word_count_read, .write = word_count_write
};

static struct miscdevice misc =
{
    .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops
};

static int word_count_init(void)
{
    ret = misc_register(&misc);              //成功注册，返回非0整数，失败返回0
    printk("word_count_init_success:%d\n",ret);
    return ret;
}

static void word_count_exit(void)
{
    misc_deregister(&misc);
    printk("word_count_exit_success\n");
}

module_init(word_count_init);
module_exit(word_count_exit);

MODULE_AUTHOR("MC");
MODULE_DESCRIPTION("statistics of word count.");
MODULE_ALIAS("word count module.");
MODULE_LICENSE("GPL");


