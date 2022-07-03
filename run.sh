#!/bin/sh

clear

a=$(find ./DLLS -type d)
b=""
for i in $(echo $a | tr " " "\n")
do
    b+=$i:
done


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./libs/:$b
filePath=output/LTE_Editor.out
make $filePath || exit 1
$filePath

echo "program exited with code $?"