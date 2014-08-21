#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/poll.h>
//  定义设备文件名
#define DEVICE_NAME "poll_select"
#define MAX_BUFFER_SIZE 20

static char buffer[MAX_BUFFER_SIZE];
static int buffer_char_count = 0;
static wait_queue_head_t my_queue;
struct semaphore sem;
