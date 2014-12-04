
make -C /usr/src/linux-headers-3.11.0-15-generic/ M=$PWD
rmmod word_count
insmod $PWD/word_count.ko

