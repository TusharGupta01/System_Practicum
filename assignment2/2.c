//Commands are case sensitive

#include <stdio.h>
#include <stdlib.h> //for getenv()
#include <unistd.h>
#define PATH_MAX 200
#define HOST_NAME_MAX 50
void clearSpace() {
  int ch;
  ch = getchar();
  while(ch == ' ' || ch == '\t')
    ch = getchar();
  ungetc(ch, stdin);
}

void clear (void)
{ 
  while ( getchar() != '\n' );
}

void printEnvList(char ** envp) {
  char ** env;
  for(env = envp; *env != NULL; env++) {
    printf("%s\n", *env);
  }
}

void dumpInput() {
  int ch;
  clearSpace();
  while((ch = getchar())!= '\n') {
    if(ch == ' ' || ch == '\t') {
      clearSpace();
      printf(" ");
    }
    else
      printf("%c", ch);
  }
  printf("\n");
}



int main(int argc, char * argv[], char * envp[]) {
  char s[100]; //Maximum assumed length of any command word
  int ch;
  char * temp;
  char * hostName;
  hostName = (char *) malloc(sizeof(char) * HOST_NAME_MAX);
  gethostname(hostName, HOST_NAME_MAX);
  FILE * fp = stdin;
  int flag = 0; //0 Indi
  if(argc > 1) {
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
      printf("Unable to open file. User can enter commands manually.\n");
      fp = stdin;
    }
  }
  while(1) {
    printf("|%s@%s:%s$| ", getenv("USER"), hostName, getcwd(temp,PATH_MAX));
   
    fscanf(stdin, "%s", s); //Read next command
    
    if(strcmp(s, "clr") == 0) {
      clear();
      printf("\033[2J\033[1;1H");
      /* The first one (\033[2J) clears the entire screen (J) from top to bottom (2). The second code (\033[1;1H) positions the cursor at row 1, column 1.*/
    }

    else if(strcmp(s, "HOME") == 0) {
      printf("%s\n", getenv(s));
    }

    else if(strcmp(s, "environ") == 0 ) {
      printEnvList(envp);
    }

    else if(strcmp(s, "echo") == 0) {
      dumpInput();
    }

    else if(strcmp(s, "quit") == 0) {
      exit(0);
    }

    else if(strcmp(s, "pwd") == 0) {
      printf("%s\n", getenv("PWD"));
    }

    else if(strcmp(s, "pause") == 0) {
      while((ch = getchar()) != '\n'); //For clearing input buffer from the same line of pause
      printf("Press enter or return key to resume.");
      //while((ch = getchar()) != '\n');
      //pause();
    }

    else if(strcmp(s, "cd") == 0) {
      clearSpace();
      if((ch = getchar()) == '\n') 
	printf("%s\n", getcwd(temp, PATH_MAX));
      else {
	ungetc(ch, fp);
	scanf("%s", s);
	if(chdir(s) != 0)
	  printf("Error changing directory.\n");
	else setenv("PWD", getcwd(temp, PATH_MAX), 1);
      }
    }

  }//End of while(1) 
  return 0;
}
