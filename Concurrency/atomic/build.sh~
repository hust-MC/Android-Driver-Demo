#build.sh

atom=1
make -C  /usr/src/linux-headers-3.11.0-15-generic/ M=/root/android/demo/atomic/src

rmmod atomic

echo 'enter the value (atom)'
read atom
insmod src/atomic.ko atom=$atom
