//The program calculates the EER from a set of input values given through stdin of FRR and FAR in prescribed format.
//The program also creates a file named temp.txt which just contains the value of threshold*1mn where the EER occurs.
#include <stdio.h>
#include <string.h>
#define RESOLUTION 1000001

double absDiff(double x, double y) {
  if(x > y)
    return x - y;
  else return y - x;
}

int main()
{
  char line[60];
  int dump;
  int threshold;
  double frr, frr_prev, far, far_prev;
  double min = 101.0;
  double diff;
  while(fgets(line, 59, stdin)) {
    sscanf(line, "%d%d%lf%d%d%lf", &threshold, &dump, &frr, &dump, &dump, &far);
    diff = absDiff(frr, far);
     if(diff <= min)
      min = diff;
    else break;
     frr_prev = frr;
     far_prev = far;
  }
  printf("FRR at EER: %f\nFAR at EER: %f\nDiff at EER: %f\nThreshold at EER: %d\n", frr_prev, far_prev, absDiff(frr_prev, far_prev), --threshold);
  FILE * fp = fopen("temp.txt", "w");
  fprintf(fp, "%d", threshold);
  return 0;
}
