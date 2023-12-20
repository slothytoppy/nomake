#ifndef COMPILATION_IMPLEMENTATION
int exec(char* args[]);
int len(char* str1);
char* fext(char* file);
char* base(char* path);
int compile_all(DIR* dir);
#endif

#ifdef COMPILATION_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include <sys/wait.h>
#include <sys/stat.h>

int exec(char* args[]){
  pid_t id=fork();
  int child_status;
  if(id==0){
    execvp(args[0], args);
  } 
  if(id<0){
    printf("forking failed");
    return -1;
  }
  wait(&child_status);
  return 0;
}

int len(char* str1){
if(str1==NULL) return -1;
int i=0;
  while(*str1++){
  i++;
  }
  return i;
}

char* ext(char* filename){
int i;
char* ext={0};
int sz=len(filename);
if(sz<0) return NULL;
  for(i=0; i<sz; i++){
    if(filename[i]=='.'){ 
    ext=strdup(filename);
    ext=strrchr(filename, '.');
    return ext;
    }
  } 
  return filename;
}

char* base(char* file){
  if (file==NULL) return NULL;
  char *retStr;
  char *lastExt;
  if ((retStr = malloc (strlen (file) + 1)) == NULL) return NULL;
  strcpy (retStr, file);
  lastExt = strrchr (retStr, '.');
  if (lastExt != NULL)
    *lastExt = '\0';
  return retStr;
}

// add compile_all functionality

int compile_all(char* directory){
struct stat fi;
struct dirent *dirent;
DIR* DIR;
DIR=opendir(directory);
  if(DIR){
    while((dirent=readdir(DIR))!=NULL){
      if(strlen(dirent->d_name)!=1 && dirent->d_name[1]!='.' != strlen(dirent->d_name)!=2 && strcmp(dirent->d_name, "..")!=0){
      if(strcmp(ext(dirent->d_name), ".c")==0){
	printf("{%s}\n", dirent->d_name);
      }
      }
    }
  }
      closedir(DIR);
}
#endif