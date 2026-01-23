#! /bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source> <destination>"
    exit 1
fi


for i in {1..4}; do
    biggest=$(bash biggest.sh $1)
    mv "$biggest" "$2"
    echo "$biggest" vers "$2"
done