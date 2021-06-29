#!/bin/sh

gnuplot <<EOF
set term pngcairo size 800,600
set output 'os.png'
set xlabel 'seconds'
set ylabel 'CPU%'
plot \
'cpu0.dat' u 1:3 w lp title 'cpu0 usr',\
'cpu0.dat' u 1:5 w lp title 'cpu0 sys',\
'cpu0.dat' u 1:9 w lp title 'cpu0 softirq',\
'cpu1.dat' u 1:3 w lp title 'cpu1 usr',\
'cpu1.dat' u 1:5 w lp title 'cpu1 sys',\
'cpu1.dat' u 1:9 w lp title 'cpu1 softirq',\
'cpu2.dat' u 1:3 w lp title 'cpu2 usr',\
'cpu2.dat' u 1:5 w lp title 'cpu2 sys',\
'cpu2.dat' u 1:9 w lp title 'cpu2 softirq',\
'cpu3.dat' u 1:3 w lp title 'cpu3 usr',\
'cpu3.dat' u 1:5 w lp title 'cpu3 sys',\
'cpu3.dat' u 1:9 w lp title 'cpu3 softirq',\
'cpu4.dat' u 1:3 w lp title 'cpu4 usr',\
'cpu4.dat' u 1:5 w lp title 'cpu4 sys',\
'cpu4.dat' u 1:9 w lp title 'cpu4 softirq',\
'cpu5.dat' u 1:3 w lp title 'cpu5 usr',\
'cpu5.dat' u 1:5 w lp title 'cpu5 sys',\
'cpu5.dat' u 1:9 w lp title 'cpu5 softirq',\
'cpu6.dat' u 1:3 w lp title 'cpu6 usr',\
'cpu6.dat' u 1:5 w lp title 'cpu6 sys',\
'cpu6.dat' u 1:9 w lp title 'cpu6 softirq'
EOF

