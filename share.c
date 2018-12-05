#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void receive_input(char * statement, char * input, int size){
  printf("%s\n",statement);
  fgets(input,size,stdin);
  strtok(input,"\n");
}

int main(){
  key_t key = ftok("share.c", 999);
  int shmid = shmget(key, 200, 0644 | IPC_CREAT);
  char * data = shmat(shmid,0,0);
  char in[100]; 
  while(1){
    if(!strlen(data)) printf("new segment\n");
    else printf("segment contains: %s\n", data);
    receive_input("Do you want to change data in segment? (type y/n)",in,100);
    if(!strcmp(in,"y")){
      receive_input("Delete or modify? (type d/a)",in,100);
      if(!strcmp(in,"d")){
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
        printf("segment contains: %s\n", data);
        break;
      } 
      else if(!strcmp(in,"a")) receive_input("type your modification: ",data,200);
    }
  }
  return 0;
}
