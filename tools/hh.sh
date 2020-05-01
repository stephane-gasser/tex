#!/bin/bash
for file in copie/*.h
	do
	base=$(basename $file)
	header=${base%.h}
	upper=${header^^}
	echo "#ifndef ${upper}_H" > $base
	echo "#define ${upper}_H" >> $base
	cat $file >> $base
	echo "#endif" >> $base
	done
