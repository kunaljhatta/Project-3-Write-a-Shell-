#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_PATH_LEN 200

int main (){
  char input[2048];
  char *token;
  char *argv[128];
  char path[MAX_PATH_LEN];
  int i;
  
  while(1){
    fflush(stdout);
    getcwd(path, MAX_PATH_LEN);
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