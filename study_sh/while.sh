#!/bin/sh

a=100
b=1
while [ $b -lt $a ]
do
  echo $b
	let b="$b*2"
done
echo $b
