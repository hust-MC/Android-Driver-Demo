#! /bin/bash

make -C /usr/src/linux-headers-3.11.0-15-generic/ M=$PWD/src

rmmod poll_select_mc

insmod src/poll_select_mc.ko
