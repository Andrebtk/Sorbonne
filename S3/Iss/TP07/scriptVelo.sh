rep=0
for i in $(cat velib.json | tr ',' '\n' | grep "nbbike\"" | cut -d ':' -f 2); do
    rep=$((rep+$i))
done
echo $rep