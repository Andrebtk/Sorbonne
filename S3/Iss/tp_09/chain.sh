[ $# -ne 1 ] && echo "usage: $0 <n>" && exit

spaces=""
count=$(($1 + 1))
while [ $count -gt 1 ]; do
	spaces="$spaces "
	count=$(($count - 1))
done


if [ $1 -gt 0 ]; then
	bash "$0" $(($1 - 1)) &
	child_pid=$!
fi


for _ in {1..99}; do
	echo "Ola :${spaces}O"
	sleep 1
done


if [ $1 -gt 0 ]; then
	wait $child_pid
fi