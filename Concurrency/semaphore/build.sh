#! /bin/bash

device = 1
echo "please choose the device"
echo "1.PC"
echo "2.ARM"

read device

echo $device

case $device in

1)
make -C /usr/src/linux-headers-3.11.0-15-generic/ M=/root/android/demo/Concurrency/semaphore/src
rmmod semaphore
insmod /root/android/demo/Concurrency/semaphore/src/semaphore.ko;;

2)
make -C /root/android/source_code/linux-3.0.8 M=/root/android/demo/Concurrency/semaphore/src
adb push /root/android/demo/Concurrency/semaphore/src/semaphore.ko /data/local
adb shell rmmod semaphore
adb shell insmod /data/local/semaphore.ko;;


*)
echo "error"

esac


