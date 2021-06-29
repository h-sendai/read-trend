#!/bin/sh

gnuplot <<EOF
set term pngcairo size 800,600
set output 'prog.png'
set ytics nomirror
set y2tics nomirror
set y2range [0:1500]
set y2tics 0,200
set my2tics 2
set ylabel 'cpu%'
set y2label 'MB/s'
set xlabel 'seconds'
plot \
'prog-cpu.dat' u 1:3 w lp title 'prog usr',\
'prog-cpu.dat' u 1:5 w lp title 'prog sys',\
'run.dat' u 1:2 w lp title 'MB/s' ax x1y2
EOF
