#!/bin/bash
#Program for Addition, Substraction, Multiplication, Division and Remainder

ch="y"
echo "1 : Addition"
echo "2 : Substraction"
echo "3 : Multiplication"
echo "4 : Division"
echo "5 : Remainder"
echo "6 : Exit"
while [ $ch == "y" ]
do
    echo "Enter your choice "
    read value
    echo "Enter the first number"
    read a
    echo "Enter the second number"
    read b
    case $value in
        1)
            r=$(( $a + $b ))
            echo "Result : $r";;
        2)
            r=$(( $a - $b ))
            echo "Result : $r";;
        3)
            r=$(( $a * $b ))
            echo "Result : $r";;
        4)
            r=$(( $a / $b ))
            echo "Result : $r";;
        5)
            r=$(( $a % $b ))
            echo "Result : $r";;

        *)
            echo "Invalid Choice"
            ;;
        esac
        echo "Do you want to continue ? "
        read ch

done
