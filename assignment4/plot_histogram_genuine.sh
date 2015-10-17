out='g1_histogram_genuine1.png'
gnuplot << PLOTTHIS
set term postscript eps enhanced color  "Helvetica" 32

set terminal png
set output "${out}"
set autoscale
unset log                              
unset label
set grid 
set title "SEQ"
set key right top
#set ylabel "Frequency (%)"
#set xlabel "Score (%)"
#set format x "10^{%L}"

##########################
#set xrange [9100:9500]
#set yrange [0:0.8]
#########################

#set xrange [0.2:3]
set yrange [0:13]
set xrange [0:300]
#set xtics (0.0001,0.001,0.01,0.1,1,10,100)
#set xtics (0.2,0.25,0.5,0.75,1)

#set xlabel "Threshold"
#set ylabel "FAR/FRR (%)"

set xlabel "N"
set ylabel "Time"

##############################################################

plot "seq.txt" using 1:2  w linespoints, \
     "par.txt" using 1:2  w linespoints


##############################################################

##############################################################
pause mouse
PLOTTHIS