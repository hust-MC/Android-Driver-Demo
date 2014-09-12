#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

static struct workqueue_struct *my_wq;				//定义一个工作队列结构体指针

/*
*通过在work_struct结构体外在套结构体的方式传递数据data
*/
struct work_struct_data
{
	struct work_struct my_work;
	void *data;
} *wsdata;

//工作队列处理函数
static void work_handler(struct work_struct *work)
{
	struct work_struct_data *wsdata = (struct work_struct_data *)work;
	printk(KERN_ALERT "work_handler data:%s\n", (char*)wsdata->data);
}

static int __init demo_init(void)
{

	int ret = 0;
	my_wq = create_workqueue("my_queue");


	if (my_wq)
	{	
		//动态为data分配空间
		wsdata = (struct work_struct_data *) kmalloc(sizeof(struct work_struct_data),
		        GFP_KERNEL);
		wsdata->data = (char*)"hello world";
		if (wsdata)
		{
			INIT_WORK(&wsdata->my_work, work_handler);	//初始化work_struct变量（制定处理函数）
			ret = queue_work(my_wq, &wsdata->my_work);	//将work_struct添加到刚创建的工作队列my_wq中
		}
	}

	printk(KERN_ALERT "demo_init.\n");
	return ret;
}

/*
*驱动卸载函数：
*通过两个步骤注销创建的工作队列
*/
static void __exit demo_exit(void)
{
	//1.检测工作队列中的工作是否都完成了
	flush_workqueue(my_wq);
	//2.销毁工作队列
	destroy_workqueue(my_wq);
	printk(KERN_ALERT "demo_exit.\n");
}
MODULE_LICENSE("GPL");
module_init(demo_init);
module_exit(demo_exit);
