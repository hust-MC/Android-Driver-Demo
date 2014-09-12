#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>

#include <asm/uaccess.h>
#include <asm/spinlock.h>


#define debug 1

#if debug
	#define print_debug(x,...) printk(x,##__VA_ARGS__)
#else
	#define print_debug(x,...) do{}while(0)
#endif

#endif
