#!/bin/bash
#Palindrome numbers between two given numbers as command line arguments
num1=$1
num2=$2
echo "Palindrome numbers between $num1 and $num2"

for (( i=$num1;i<=$num2;i++ ))
do
    rev=0
    num=$i
    while [ $num -gt 0 ]
    do
        digit=$(( $num % 10 ))
        rev=$(( $rev* 10 + $digit ))
        num=$(( $num / 10 ))
    done
    if [ $i -eq $rev ]
    then
        echo $i
    fi
done
