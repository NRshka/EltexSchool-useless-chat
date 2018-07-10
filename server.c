#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <pthread.h>
#include "msgtypes.h"

int queue_system;
char nick[] = "server_message";
char msg_ok[] = "connected";
struct msg_t message;

void listen_system(){
  while(1){
    msgrcv(queue_system, &message, sizeof(message) - sizeof(long), 0, 0);  // ждем сообщение
    printf("Client %s send: %s\n", message.nickname, message.body);
    sleep(2);
   }
}

int main(int argc, char * argv[])
{
    pthread_t reg_nicks;
    int key = ftok("txt.txt", 'A');
    queue_system = msgget(key, 0666 | IPC_CREAT);  // создаем очередь сообщений
    //Заполняем ответ:
    message.mtype = 1;
    strcpy(message.nickname, nick);
    strcpy(message.body, msg_ok);
    
    pthread_create(&reg_nicks, NULL, listen_system, NULL);
    pthread_join(reg_nicks, NULL);

    msgctl(queue_system, IPC_RMID, 0);  // удаляем очередь
    return EXIT_SUCCESS;
}