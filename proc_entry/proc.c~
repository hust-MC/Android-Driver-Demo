#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define PROC_NAME_BASE		"proc_demo"	//虚拟文件系统目录名
#define PROC_NAME		"bin2dec"	//虚拟文件系统文件名
#define PROC_NAME_READONLY	"readonly"	//只读虚拟文件系统文件名

#define DEBUG 1
#if DEBUG
#define de_pri(x,...)	printk(x,##__VA_ARGS_) 
#else
#define de_pri(x,...)	do{} while(0)
#endif

static long decimal;

//依次申明结构体指针
static struct proc_dir_entry *proc_entry_base = NULL;
static struct proc_dir_entry *proc_entry = NULL;
static struct proc_dir_entry *proc_entry_readonly = NULL;


static int proc_demo_readonly(char *page, char **start, off_t off, int count ,int *eof, void *data)
{
	int len;
	//不允许偏移读取
	if(off > 0)
	{
		*eof = 1;
		return 0;
	}
	len = sprintf(page, "debug infor\n");	//将要读取的消息写入page指针指向的缓冲区，page缓冲区中的数据都将作为虚拟文件中的数据
	return len;		//返回读取消息的长度
}

static int proc_demo_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int len;
	if(off > 0)
	{
		*eof = 1;
		return 0;
	}
	len = sprintf(page, "%ld",decimal);	//将转换后的十六进制数写入page缓冲区
	return len;
}

static int proc_demo_write(struct file *file, const char _user *buffer, unsigned long const, void *data)
{
	char buf[count];
	if(copy_from_user(buf, buffer, count))
	{
		return -EFAULT;
	}
	else
	{
		//将二进制数转换为十进制数
		//simple_strtoul函数用于将字符串形式的二进制到十六进制数转换位十进制数据
		//最后一个参数表示待转换的进制
		decimal = simple_strtoul(buf, NULL, 2);
		return count;	
	}
}

static int proc_init(void)
{
	proc_entry_base = proc_mkdir(PROC_NAME_BASE,NULL);	//创建虚拟目录(/proc/proc_demo)
	if(proc_entry_base == NULL)
	{
		de_pri("Counldn't create proc entry dir\n");
		return -ENOMEM;
	}

	proc_entry = create_proc_entry(PROC_NAME, 666, proc_entry_base);		//创建虚拟文件
	proc_entry_readonly = create_proc_read_only(PROC_NAME,444,proc_entry_base,proc_demo_readonly,NULL);	//创建只读虚拟文件
	if(proc_entry == NULL || proc_entry_readonly)
	{
		de_pir("Counldn't create proc entry");	
		return -ENOMEM;	
	}
	else
	{
		proc_entry->read_proc = proc_demo_read;
		proc_entry->write_proc = proc_demo_write;
	}
	return 0;
}

//卸载Linux驱动函数
static void proc_exit(void)
{
	if(proc_entry != NULL)
	{
		remove_proc_entry(PROC_NAME, proc_entry_base);
	}
	if(proc_entry_readonly != NULL)
	{
		remove_proc_entry(PROC_NAME_READONLY, protc_entry_base);
	}
	if(proc_entry_base != NULL)
	{
		remove_proc_entry(PROC_NAME_BASE,NULL);
	}
}

module_init(proc_init);
module_init(proc_exit);
