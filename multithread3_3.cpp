#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include<time.h>
#include<fstream>

#define dbg(x) cerr<<#x<<" is "<<x<<endl;
using namespace std;
int size = 300;
int num_thrd;
 
int A[3000][3000], B[3000][3000], C[3000][3000];
int i;
void* multiply(void* slice){
  int *s = (int*)slice;        
  int start = (*s * size)/num_thrd;
  int end = ((*s + 1) * size)/num_thrd;
  int i,j,k;
  for (i = start; i < end; i++){  
    for (j = 0; j < size; j++){
      C[i][j] = 0;
      for ( k = 0; k < size; k++)
	C[i][j] += A[i][k]*B[k][j];
    }
  }
   return 0;
}
 
int main(int argc, char* argv[]){
  size = atoi(argv[1]);
  num_thrd = 4;
  
  int j, val = 0;
   clock_t startTime = clock();
   ofstream myfile;
  myfile.open ("par.txt");
  for(int l = 3;l < 300;l++){
    size = l;
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
      A[i][j] = val++;
    }
  }

  val = 0;
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
      B[i][j] = val++;
    }
  }
  pthread_t thread[size]; 
  for (i = 1; i < num_thrd; i++){
    if (pthread_create (&thread[i], NULL, multiply, (void*)(&i))!=0){
      perror("Can't create thread");
      free(thread);
      exit(-1);
    }
  }
  for (i = 1; i < num_thrd; i++)
    pthread_join (thread[i], NULL);
  float secsElapsed = (float)(clock() - startTime)/CLOCKS_PER_SEC;
  myfile<<l<<"\t" <<secsElapsed<<"\n";
  }
  return 0;
 
}
