#!/bin/sh

awk '{print $1+10, $2}' run.log > run.dat
grep ' cpu ' read-stat-cpu.out > cpu-sum.dat
grep 'cpu7' read-stat-cpu.out > prog-cpu.dat
for i in {0..6}; do
    cpu_num=cpu$i
    grep "$cpu_num" read-stat-cpu.out > $cpu_num.dat
done
