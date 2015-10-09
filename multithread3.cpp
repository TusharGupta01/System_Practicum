#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<time.h>
#include<fstream>
using namespace std;

int main(int argc,char *argv[]){
  int num;
  sscanf (argv[1], "%i", &num);
  int a[num][num],b[num][num];
  int i,j,k;
   
  clock_t startTime = clock();

  ofstream myfile;
  myfile.open ("seq.txt");
  for(int l = 3 ;l < 300;l++){
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
    int c[i][j];
    int sum = 0;
    for (i = 0; i < num; i++) {
      for (j = 0; j < num; j++) {
	sum = 0;
	for (k = 0; k < num; k++) {
	  sum = sum + a[i][k] * b[k][j];
	}
	c[i][j] = sum;
      }
    }
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
