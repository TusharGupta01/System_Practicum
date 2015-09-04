/* 
Program to find FAR, FRR and other statistics 
Author = Tushar Gupta, Gopal Krishan Aggarwal
Group = 20 
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cmath>
#define RESOLUTION 1000001                                                // Number of threshold

using namespace std;
int main(){
    int *score0 = new int[1000005];                                       // Score array to implement Histogram 
    int *score1 = new int[1000005];
    char filename[20];    

    cout<<"Give file name:  ";
    cin>> filename;                                                       // Take file from user
    FILE *f;
    f = fopen(filename, "r");
    char line[60];
    int a,b,c,d,e;
    double g;

    int TI = 0,TG = 0;                                                    // Total Imposter and Total Genuine
    double min = 10,max = 0;
    int temp = 1,temp1 = 1,temp2,temp3,temp4,temp5;
    FILE *fo = fopen("CRR.sts","w");

    while(fgets(line,59,f)){                                            
        sscanf(line," %d %d %d %d %d %lf",&a,&b,&c,&d,&e,&g);             // Input a line from file 
        if(e == 1){                                                       
            int index = g * 1000000;
            score1[index] = score1[index] + 1;
            TG += 1;
        }
        else if(e == 0){
            int index = g * 1000000;
            score0[index] = score0[index] + 1;
            TI += 1;
        }
	int value = 1;
	if(temp != temp2){
	  value = 0;
	}
	if(temp != a || temp1 != b){                                       // Calculation of CRR
	  fprintf(fo, "%d   %d   [(%d,%d)%f]   [(%d,%d)%f]   %d",temp,temp1,temp2,temp3,min,temp4,temp5,max,value);
	  fprintf(fo, "%c", '\n'); 
	  max = 0;
	  min = 10;
	}
	if(min > g){                                                      // Min score for a particular image of a subject id
	  min = g;
	  temp2 = c;
	  temp3 = d;
	}
	if(max < g){
	  max = g;
	  temp4 = c;
	  temp5 = d;
	}
	temp = a;
	temp1 = b;
    }
    fprintf(fo, "%d   %d   [(%d,%d)%f]   [(%d,%d)%f]   1",temp,temp1,temp2,temp3,min,temp4,temp5,max); 

    for(int i = 1;i < RESOLUTION;i++){                                    // Cumulative scores
        score0[i] = (score0[i - 1] + score0[i]);
        score1[i] = (score1[i - 1] + score1[i]);
    }
    int Data_point_Genuine = 0;                                           // Data point for Genuine
    int Data_point_Imposter = 0;                                          // Data points for Imposter
    long long int sumG = 0;
    long long int sumI = 0;

    FILE *fo1;
    fo1 = fopen("L4_FAR_FRR_Data.dat", "w");
    FILE *fo4;
    fo4 = fopen("G_Hist.dat", "w");
    FILE *fo5;
    fo5 = fopen("I_Hist.dat", "w");
    double EER = 10.0,EER_threshold;

// Calculation of FAR,FRR,Mean,Data points
    for(int i = 0; i < RESOLUTION;i++){                   
        double FRR = (double(TG - score1[i]) / double(TG));
        double FAR = double(score0[i]) / double(TI);
        fprintf(fo1,"%d %d %lf %d %d %lf",i,(TG - score1[i]),FRR*100,i,score0[i],FAR*100);
        fprintf(fo1, "%c", '\n');
	if(i == 0 && score0[i] != 0){
	  fprintf(fo5,"%d    %lf",i,100 * double(score0[i])/double(TI));
	    fprintf(fo5, "%c", '\n');
	    Data_point_Imposter += 1;
	    sumI += i;
	}  
	else if(i == 0 && score1[i] != 0){
	    fprintf(fo4,"%d    %lf",i,100 * double(score1[i])/double(TG));
	    fprintf(fo4, "%c", '\n');
	    Data_point_Genuine += 1;
	    sumG += i;
	}
	else if(i > 0 && score0[i]-score0[i - 1] != 0){
	    fprintf(fo5,"%d    %lf",i,100 * double(score0[i]-score0[i - 1])/double(TI));
	    fprintf(fo5, "%c", '\n');
	    Data_point_Imposter += 1;
	    sumI += i;
	} 
	else if(i > 0 && score1[i]-score1[i - 1] != 0){
	    fprintf(fo4,"%d    %lf",i,100 * double(score1[i]-score1[i - 1])/double(TG));
	    fprintf(fo4, "%c", '\n');
	    Data_point_Genuine += 1;
	    sumG += i;
	}
	if(EER > abs(double(FRR) - double(FAR))){
	  EER = abs(double(FRR) - double(FAR));
	  EER_threshold = i;
	}
     }

// Calculation of standard deviations
    double meanI = double(sumI)/double(Data_point_Imposter);
    double meanG = double(sumG)/double(Data_point_Genuine);
    double Stand_dev_G = 0.0,Stand_dev_I = 0.0;
    for(int i = 0; i < RESOLUTION;i++){
	if(i == 0 && score0[i] != 0){
	    Stand_dev_I = (i - meanI) * (i - meanI); 
	}  
	else if(i == 0 && score1[i] != 0){
	  Stand_dev_G = (i - meanG) * (i - meanG);
	}
	else if(i > 0 && score0[i]-score0[i - 1] != 0){
	  Stand_dev_I = (i - meanI) * (i - meanI);
	} 
	else if(i > 0 && score1[i]-score1[i - 1] != 0){
	  Stand_dev_G = (i - meanG) * (i - meanG);
	}
    }

    Stand_dev_I = sqrt(Stand_dev_I);
    Stand_dev_G = sqrt(Stand_dev_G);

    rewind(f);                                                                  // Seeking/Rewind the file to initial
    FILE *fo2;
    fo2 = fopen("L4.FR", "w");
    FILE *fo3;
    fo3 = fopen("L4.FA", "w");
    while(fgets(line,59,f)){                                                   // Calculating FR at threhold
        sscanf(line," %d %d %d %d %d %lf",&a,&b,&c,&d,&e,&g);
	if(g > (EER_threshold/1000000) && e == 1){
	    fprintf(fo2,"%d    %d    %d    %d    %d    %lf",a,b,c,d,e,g);
	    fprintf(fo2, "%c", '\n');
	}
	else if(g <= (EER_threshold/1000000) && e == 0){                       // Calculationg FA at threshold
	    fprintf(fo3,"%d    %d    %d    %d    %d    %lf",a,b,c,d,e,g);
	    fprintf(fo3, "%c", '\n');
	}
    }
cout<<EER<<" "<<EER_threshold<<" "<<meanI<<" "<<meanG<<" "<< Stand_dev_I<<" "<<Stand_dev_G<<" "<<Data_point_Genuine<<" "<<Data_point_Imposter<<"\n";
}

  
