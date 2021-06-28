#!/bin/zsh

# sample script to run read-trend and read /proc/stat to get cpu usage

read-stat-cpu > read-stat-cpu.out &
sleep 10
taskset -c 7 timeout 10.1 ../read-trend hspc01-texp0:1234 > run.log
sleep 10
pkill -f read-stat-cpu
