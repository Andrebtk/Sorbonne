[ $# -ne 1 ] && echo "usage: $0 <n>" && exit

spaces=""

count=$1
while [ $count -gt 1 ]; do
	spaces="$spaces "
	count=$(($count - 1))
done

echo "Ola :$spaces O"

if [ $1 -gt 1 ]; then
	bash "$0" $(($1 - 1)) &
	kill -SIGTSTP $$
fi
