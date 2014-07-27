/*
 * test_atomic.c
 *
 *  Created on: 2014年7月27日
 *      Author: root
 */

#include <stdio.h>
#include <errno.h>

int main()
{
	int handler = open("/dev/atomic", 0);			//打开设备文件
	printf("handler:%d\n",handler);					//若为0则打开失败
	if(handler > 0)
	{
		getchar();
		close(handler);
	}
	else
	{
		printf("errno:%d\n",errno);
	}
}
