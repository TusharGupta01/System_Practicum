//Reports all the genuine matchings that got rejected at EER
//Takes the name of file which contains threshold*1mn as its first argument and prints all those values to stdout which are Falsely Rejected at EER.
#include <stdio.h>
#include <string.h>
#define RESOLUTION 1000001
int main(int argc, char * argv[0])
{
  char line[60];
  int dump, gORi;
  double score;
 
  int threshold;
  FILE * fp = fopen(argv[1], "r");
  fscanf(fp, "%d", &threshold);
  fclose(fp);
  printf("Falsely Rejected entries at EER which is %lf:\n", threshold/1000000.0);
  while(fgets(line, 59, stdin)) {
    sscanf(line, "%d%d%d%d%d%lf", &dump, &dump, &dump, &dump, &gORi, &score);
    if(gORi == 1 && (score*(RESOLUTION-1)) > threshold)
      printf("%s", line);
  }
  
  return 0;
}
