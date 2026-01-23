dd if=/dev/urandom of=/tmp/iss bs=1b count=5000000 &

while true; do
	sleep 1
	kill -s SIGUSR1 $!
done

rm /tmp/iss
