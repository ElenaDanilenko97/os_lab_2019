#! /bin/cat

i=0
sum=0
for an_arg in $* ; #для всех аргументов
#for an_arg in $(cat numbrs.txt) ; 
do
  sum=$(($sum + $an_arg))
  i=$(($i+1))
done
echo "kolichestvo argumentov:" 
echo $i
echo "srednee arifmetichesloe:" 
expr $sum / $i # вычисляет значение выражения