#include<pthread.h>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<time.h>
#include<fstream>
using namespace std;
int num;
int c[3001][3001];
int a[3001][3001],b[3001][3001];

void *thread_Multiply_Matrix(void *para){
  int i,j,k;
  for(i = 1;i < num;i += 2){
    for(j = 0;j < num;j++){
      for(k = 0;k < num;k++){                    
	c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  pthread_exit(NULL);
}
int main(int argc,char *argv[]){
  pthread_t tid;
  clock_t startTime = clock();
  sscanf (argv[1], "%i", &num);
  int i,j,k;
  ofstream myfile;
  myfile.open ("par.txt");
  for(int l = 3;i < 300;l++){
    num = l;
    for (i = 0; i < num; i++) {
      for (j = 0; j < num; j++) {
	a[i][j] = 1;
      }
    }
    for (i = 0; i < num; i++) {
      for (j = 0; j < num; j++) {
	b[i][j] = 1;
      }
    }
    int sum = 0;
    for(i = 0;i < num;i++){
      for(j = 0;j < num;j++){
	c[i][j] = 0;
      }
    }
    pthread_create(&tid,NULL,thread_Multiply_Matrix,NULL);
    for(i = 0;i < num;i = i+2){
      for(j = 0;j < num;j++){
        for(k = 0;k < num;k++){
          c[i][j]+=a[i][k] * b[k][j];
        }
      }
    }
        
    pthread_join(tid,NULL);
    float secsElapsed = (float)(clock() - startTime)/CLOCKS_PER_SEC;
    myfile <<secsElapsed<<"\n";
  }
  myfile.close();
    /*for (i = 0; i < num; i++) {
      for (j = 0; j < num; j++) {
      cout<<c[i][j]<<" ";
      }
      cout<<"\n";
      }*/
  }
