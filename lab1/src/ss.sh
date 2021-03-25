#! /bin/cat
echo -n > numbrs.txt
count=0
MAXCOUNT=149
while [ "$count" -le $MAXCOUNT ]       # Генерация 10 ($MAXCOUNT) случайных чисел.
do
  number=$RANDOM #генерирую случайное число
  echo $number >> /projects/os_lab_2019/lab1/src/numbrs.txt #отправляю знвчение в файл
  let "count += 1"  #let - производить арифметические операции
done