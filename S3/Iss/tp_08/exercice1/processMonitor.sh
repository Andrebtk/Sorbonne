[ $# -eq 0 ] && echo "usage: $0 <pid>" && exit -1

for i in {0..60}; do
    sleep 1
    ps o pid,ppid,state --pid $1
done