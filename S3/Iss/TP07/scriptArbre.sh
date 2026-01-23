#Option1
cat arbresremarquablesparis.csv | tail -n +2 | cut -d ';' -f 8 | sort | uniq -c | sort -n | grep -E "5E | 6E | 7E | 13E | 14E" | tail -n 1 | tr -s ' ' ' ' | cut -d ' ' -f 3-5

#Option2
cat arbresremarquablesparis.csv | grep -E "5E | 6E | 7E | 13E | 14E" | tail -n +2 | cut -d ';' -f 8 | sort | uniq -c | sort -n  | tail -n 1 | tr -s ' ' ' ' | cut -d ' ' -f 3-5