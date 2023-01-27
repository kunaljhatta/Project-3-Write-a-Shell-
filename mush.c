#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){
  char input[2048];
  char *token;
  char *argv[128];
  char path[200];
  int i;
  
  while(1){
    fflush(stdout);
    getcwd(path, 200);
    printf("~ %s $ ", path);
    fgets(input, sizeof input, stdin);
    i=0;

    if ((token=strtok(input, " \t\n\r")) !=NULL) {
      do {
        argv[i++]=token;
      } 
      while ((token=strtok(NULL, " \t\n\r")) !=NULL);
    }
    argv[i] = NULL;
        
    if(strcmp(argv[0], "cd")==0){
      if(chdir(argv[1])==-1){
        perror("ERROR");
      }
    }
    
    else if(strcmp(argv[0], "exit")==0){
      exit(0);
    }

    else{
      pid_t pid=fork();
      if(pid==0){
        execvp(argv[0], argv);
        perror("exec");
        exit(1);
      }

      else{
      wait(NULL);
      }
    }
  }
}