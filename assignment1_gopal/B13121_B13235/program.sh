gcc frr_far_histogram_crr.c -o frr_far_histogram_crr
./frr_far_histogram_crr < L4.txt > frr_far.txt
gcc eer.c -o eer
./eer < frr_far.txt > eer.txt
gcc fa.c -o fa
./fa temp.txt <L4.txt > fa.txt
gcc fr.c -o fr
./fr temp.txt <L4.txt > fr.txt
sh plot_farVsfrr.sh
sh plot_histogram_imposter.sh
sh plot_histogram_genuine.sh

#sts file can easily be created from the outputs of above programs.