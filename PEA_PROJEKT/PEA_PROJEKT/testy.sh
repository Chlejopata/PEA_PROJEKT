#!/bin/bash
echoerr()  { echo "$@" 1>&2; }
N=10
filesnumber=$( ls -Sr ./TSPLIB/ | grep -E '*.xml' | wc -l)
i=0
for f in $( ls -Sr ./TSPLIB/ | grep -E '*.xml'); do
i=$((i+1))
echoerr [$i / $filesnumber] ./TSPLIB/$f
optimal="$(cat ./TSPLIB/optimal.txt | grep -E ${f%%.xml} | cut -d' ' -f2)"
echo $optimal 
./Grafy ./TSPLIB/$f $N | grep -E '*;' |  awk -v opt=$optimal '{ route += $1; time +=$2; n++; print $1 " " $2} END { route = route / n; print "\n" route " AVG ROUTE"; print time / n " AVG TIME"; d = sqrt((opt - route)^2); print d " DIFF"; print d / opt}'
echo =========
if (($i == 70)); then 
	break
fi
done
