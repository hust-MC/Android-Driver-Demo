#!bin/bash

f="0" 


echo "1.combile drive only"
echo "2.combile app only"
echo "default for both"
read f


 case $f in
	
        1)
	make -C /usr/src/linux-headers-3.11.0-15-generic/ M=$PWD/src
	rmmod timer
	insmod src/timer.ko;; 
         
	2)
	gcc  -o test_timer timer_APP.c;;
               
	*)
        make -C /usr/src/linux-headers-3.11.0-15-generic/ M=$PWD/src
	rmmod timer
	insmod src/timer.ko
	gcc -o test_timer timer_APP.c;;

esac 


