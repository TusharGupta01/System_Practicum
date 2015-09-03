//Commands are case sensitive

#include <stdio.h>
#include <stdlib.h> //for getenv()
#include <unistd.h>
#include <string.h>
#include <dirent.h>

FILE * ifp;

void clearSpace() {
  int ch;
  ch = getc(ifp);
  while(ch == ' ' || ch == '\t')
    ch = getc(ifp);
  ungetc(ch, ifp);
}


int listDir(char * directory) {
  DIR * dir;
  struct dirent *ent;
  if((dir = opendir(directory)) != NULL) {
    //Print all the files and directories within directory
    while( (ent = readdir(dir)) != NULL) {
      printf("%s\n", ent->d_name);
    }
    closedir(dir);
  } else {
    //Could not open directory
    perror("Could not open directory.\n");
    return EXIT_FAILURE;
  }
}

void clear (void)
{ 
  while ( getc(ifp) != '\n' );
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
  while((ch = getc(ifp))!= '\n') {
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

  ifp = stdin;
  if(argc > 1) {
    ifp = fopen(argv[1], "r");
    if(ifp == NULL) {
      printf("Unable to open file. User can enter commands manually.\n");
      ifp = stdin;
    }
  }
  while(ifp) {
    printf("|%s@%s:%s$| ", getenv("USER"), hostName, getcwd(temp,PATH_MAX));
   
    fscanf(ifp, "%s", s); //Read next command
    
    if(strcmp(s, "clr") == 0) {
      clear();
      printf("\033[2J\033[1;1H");
      /* The first one (\033[2J) clears the entire screen (J) from top to bottom (2). The second code (\033[1;1H) positions the cursor at row 1, column 1.*/
    }

    else if(strcmp(s, "HOME") == 0) {
      printf("%s\n", getenv(s));
    }

    else if(strcmp(s, "dir") == 0) {
      clearSpace();
      if((ch = getchar()) == '\n') 
	listDir(getcwd(temp, PATH_MAX));
      else {
	ungetc(ch, ifp);
	fscanf(ifp, "%s", s);
	listDir(s);
      }
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
      while((ch = getc(ifp)) != '\n'); //For clearing input buffer from the same line of pause      
      printf("Press enter or return key to resume.\n");
      while((ch = getc(ifp)) != '\n');
      //pause();
    }

    else if(strcmp(s, "cd") == 0) {
      clearSpace();
      if((ch = getc(ifp)) == '\n') 
	printf("%s\n", getcwd(temp, PATH_MAX));
      else {
	ungetc(ch, ifp);
	fscanf(ifp, "%s", s);
	if(chdir(s) != 0)
	  printf("Error changing directory.\n");
	else setenv("PWD", getcwd(temp, PATH_MAX), 1);
      }
    }

  }//End of while(1) 
  return 0;
}
