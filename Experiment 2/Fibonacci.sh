#Program to print n terms in a fibonacci series

echo "How many terms ? : "
read n
a=0
b=1
echo "Fibonacci Series for first $n terms"
echo $a
echo $b
for (( i=2;i<=n;i++ ))
do
    c=$(($a+$b))
    echo $c
    a=$b
    b=$c
done
