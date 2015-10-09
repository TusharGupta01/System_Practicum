#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include<string>
using namespace std;

const int NUMBER_OF_THREADS = 4;
int num;
string str;

void * thread_talk(void * thread_nr){
  int a = *(static_cast<int*>(thread_nr));
  cout << "Thread " <<  a <<" has finished"  << endl;
  if(a == 0){
    cout<<"Take number and ";
    cout<<"take string: ";
    cin>>num;
    getline(cin,str);
  }
  else if(a == 1){
    for(int i = 0;i < str.size();i++){
      if(str[i] != ' ')
	cout<<char(str[i] + 5);
      else
	cout<<" ";
    }
    cout<<"\n";
  }
  else if(a == 2){
    int a = 1;
    int b = 1;
    if(num == 0){cout<<"1"<<"\n";}
    else if(num == 1){cout<<"1"<<"\n";}
    else {
      int temp;
      for(int i = 2;i <= num;i++){
	temp = b;
	b = b + a;
	a = temp;
      }
      cout<<b<<"\n";
    }
  }
  else if(a == 3){
    for(int i = 0;i < str.size();i++){
      if(str[i] != ' ')
	cout<<char(str[i] + 5);
      else
	cout<<" ";
    }
    cout<<"\n";
    int a = 1;
    int b = 1;
    if(num == 0){cout<<"1"<<"\n";}
    else if(num == 1){cout<<"1"<<"\n";}
    else {
      int temp;
      for(int i = 2;i <= num;i++){
	temp = b;
	b = b + a;
	a = temp;
      }
      cout<<b<<"\n";
    }
  }
  pthread_exit(NULL);
  return 0;
}

int main(){

  pthread_t thread[NUMBER_OF_THREADS];
  cout << "Starting all threads..." << endl;

  int temp_arg[NUMBER_OF_THREADS] ;

  for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++){
    temp_arg[current_t]   = current_t;

    int result = pthread_create(&thread[current_t], NULL, thread_talk, static_cast<void*>(&temp_arg[current_t]));
    pthread_join(thread[current_t], NULL);

    if (result !=0){
      cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
    }
  }
  cout << "All threads completed." ;

  return 0;
}


