#! /bin/bash

device = 1
echo "please choose the device"
echo "1.PC"
echo "2.ARM"

read device

echo $device

case $device in

1)
make -C /usr/src/linux-headers-3.11.0-15-generic/ M=/root/android/demo/Concurrency/rw_lock/src
rmmod rw_lock
insmod /root/android/demo/Concurrency/rw_lock/src/rw_lock.ko;;

2)
make -C /root/android/source_code/linux-3.0.8 M=/root/android/demo/Concurrency/rw_lock/src
adb push /root/android/demo/Concurrency/rw_lock/src/rw_lock.ko /data/local
adb shell rmmod rw_lock
adb shell insmod /data/local/rw_lock.ko;;


*)
echo "error"

esac


