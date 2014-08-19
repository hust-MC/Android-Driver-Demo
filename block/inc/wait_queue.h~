#ifndef WAIT_QUEUE_H
#define WAIT_QUEUE_H


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>  
  

  
//  定义设备文件名
#define DEVICE_NAME "wq"
#define MAX_BUFFER_SIZE 20

static char buffer[MAX_BUFFER_SIZE];
static int buffer_char_count = 0;
static wait_queue_head_t my_queue;

#define debug 1
#if debug 
	#define print_debug(x,...) printk(x,##__VA_ARGS__)
#else
	#define print_debug(x,...) do{}while(0)
#endif

#endif
