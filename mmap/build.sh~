#!bin/bash

f="0" 


echo "1.combile drive only"
echo "2.combile app only"
echo "default for both"
read f


 case $f in
	
        1)
	make -C /usr/src/linux-headers-3.11.0-15-generic/ M=$PWD/src
	rmmod mmap_shared
	insmod src/mmap_shared.ko;; 
         
	2)
	gcc  -o mmap mmap_APP.c;;
               
	*)
        make -C /usr/src/linux-headers-3.11.0-15-generic/ M=$PWD/src
	rmmod mmap_shared
	insmod src/mmap_shared.ko
	gcc -o mmap mmap_APP.c;;

esac 


