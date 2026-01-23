#! /bin/bash

trap "echo Reception SIGINT" SIGINT
trap "echo bonjouer" SIGSTOP
while true; do

	echo "il ne doit en rester qu'un"
	sleep 1
done
