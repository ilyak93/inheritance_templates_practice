#!/bin/bash

for t in $( ls *.in | cut -d \. -f1 ); do
	echo $t
	./a.out < "$t.in" > "$t.res"
	diff "$t.res" "$t.out"
	echo "is completed"
done