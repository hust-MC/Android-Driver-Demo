#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>

#include <asm/uaccess.h>
#include <asm/spinlock.h>

#include <stdlib.h>

static *data = "read";
static DEFINE_SPINLOCK(lock);

static ssize_t spinLock_read(struct file *file, char __user *buf, size_t count,
		loff_t *ppos)
{
	int size = strlen(data);
	if (copy_to_user(buf, (void*) data, size))
	{
		return -EINVAL;
	}
	else
	{
		if (spin_trylock(&lock))
		{
			//在此做个延时，用于模拟临界区代码执行
			mdelay(10000);
			spin_unlock(&lock);
		}
		else
		{
			return -EBUSY;
		}
		return size;
	}
}

static ssize_t spinLock_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	char *cmd = (char *) malloc(sizeof(char *));
	if (copy_from_user(cmd, (void*) buf, count))
	{
		return -EINVAL;
	}
	else
	{
		if(strcmp("lock\n",cmd) == 0)
		{
			spin_lock(&lock);
			spin_unlock(&lock);
		}
		else if(strcmp("trylock\n",cmd) == 0)
		{
			if(spin_trylock(&lock))
			{
				printk("spin_lock is available\n");
				spin_unlock(&lock);
			}
			else
			{
				printk("spin_lock is busy\n");
				return -EBUSY;
			}
		}
		return count;
	}
}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.read = spinLock_read,
		.write = spinLock_write
};

