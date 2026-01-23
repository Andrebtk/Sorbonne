[ $# -eq 0 ] && echo "usage: $0 <pid>" && exit -1

for i in {0..60}; do
    sleep 1
    zombie=$(ps o pid,ppid,state --pid $1 | grep 'Z' | wc -w)

    [ $zombie -ne 0 ] && echo "Le processus est devenu zombie !!!" && exit 1 
done

