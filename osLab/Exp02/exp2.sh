#!/bin/bash 
touch hello.sh 
chmod u+x hello.sh 
./hello.sh 
cat hello.sh 
echo "Number of arguments supplied: $#" 
for item in "$@" 
do 
if [ -f "$item" ] 
then 
Current location 
Home directory 
Creates script file 
Owner execute permission 
Runs script 
Displays source code 
echo "$item is a file" 
lines=$(wc -l < "$item") 
echo "Number of lines: $lines" 
elif [ -d "$item" ] 
then 
echo "$item is a directory" 
else 
echo "$item does not exist" 
fi 
done