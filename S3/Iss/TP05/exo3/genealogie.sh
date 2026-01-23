#! bin/bash

# Vérifier si un paramètre a été passé
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <PID>"
    exit 1
fi

# Vérifier que le PID existe
if [ ! -d "/proc/$1" ]; then
    echo "Error: Process with PID $1 does not exist."
    exit 1
fi

current_pid=$1
while [ "$current_pid" -ne 1 ]; do
    ppid=$(cut -d ' ' -f 4 < "/proc/$current_pid/stat")
    echo $ppid

    current_pid=$ppid

done
