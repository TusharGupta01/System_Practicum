out='g1_histogram_genuine.png'
gnuplot << PLOTTHIS
set term postscript eps enhanced color  "Helvetica" 32

set terminal png
set output "${out}"
set autoscale
unset log                              
unset label
set grid 
set title "Genuine Histogram: Frquency vs Score"
set key right top
#set ylabel "Frequency (%)"
#set xlabel "Score (%)"
#set format x "10^{%L}"

##########################
#set xrange [9100:9500]
#set yrange [0:0.8]
#########################

#set xrange [0.2:3]
set yrange [0:10]
set xrange [0:1.0]
#set xtics (0.0001,0.001,0.01,0.1,1,10,100)
#set xtics (0.2,0.25,0.5,0.75,1)

#set xlabel "Threshold"
#set ylabel "FAR/FRR (%)"

set xlabel "Score"
set ylabel "Frequency"

##############################################################

plot "genuine_histogram.txt" using 2:1  w linespoints

##############################################################

##############################################################
pause mouse
PLOTTHIS