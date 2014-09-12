#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>  
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

//  定义设备文件名
#define DEVICE_NAME "semaphore"

struct semaphore sem;

#define debug 1
#if debug
	#define print_debug(x,...) printk(x,##__VA_ARGS__)
#else   
	#define print_debug(x,...) do{}while(0)
#endif


#endif
