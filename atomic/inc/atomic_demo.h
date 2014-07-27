/*
 * atomic_demo.h
 *
 *  Created on: 2014年7月27日
 *      Author: root
 */

#ifndef ATOMIC_DEMO_H
#define ATOMIC_DEMO

#define DEBUG 1
#if DEBUG
#define print_debug(x,...) printk(x, ##__VA_ARGS__)
#else
#define print_debug(x,...) do{}  while(0)
#endif

#endif
