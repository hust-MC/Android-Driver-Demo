#ifndef RW_LOCK_H
#define RW_LOCK_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>  
#include <asm/atomic.h>
#include <linux/delay.h>
#include <linux/random.h>

#define debug 1
#if debug
	#define print_debug(x,...) printk(x,##__VA_ARGS__)
#else
	#define print_debug do{}while(0)
#endif

#endif
