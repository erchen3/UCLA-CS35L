#!/bin/bash                                                                                                                             

cat  $1 |
grep -E '<td>.+</td>' |
sed 's/<[^>]*>//g' |
sed -n '1~2!p' |
sed '/^$/d' |
tr '[:upper:]' '[:lower:]' |
tr '`' "'" |
sed 's/, /\n/g' |
sed 's/ /\n/g' |
sed "s/.*[^pk'mnwlhaeiou].*//" |
sort -u |
sed '1d'

