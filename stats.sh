#!/bin/bash

dir="$(basename $5)"

#while true
#do
    mpstat 1 1| grep -A 5 "%idle" | tail -n 1 | awk -F " " '{printf("CPU: %d%\n", 100-$12)}' > stats.txt
    free -m | grep Mem | awk -F " " '{printf("Used mem: %dM\n",$3)}' >> stats.txt
    df $5 -BG --output=avail | tail -n 1 | awk -v dir="$dir" -F " " '{printf("%s/ free: %dG\n", dir, $1)}' >> stats.txt
    iostat -y -g ALL -H -d 1 1 | grep ALL | awk -F " " '{printf("Disk : %dt/s\n",$2)}' >> stats.txt
    sar -n DEV 1 1 | grep $3 | tail -n 1 | awk -F " " '{printf("Wired: %.2f%\n",$10)}' >> stats.txt
    sar -n DEV 1 1 | grep $4 | tail -n 1 | awk -F " " '{printf("Wifi: %.2f%\n",$10)}' >> stats.txt
    cat stats.txt | nc --send-only -u $1 $2
#done
