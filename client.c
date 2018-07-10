#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <strings.h>
#include "msgtypes.h"

int main(int argc, char * argv[])
{
  int queue_system;
  int i;
  struct msg_t message;
  char buf[MAXLEN];
  int key = ftok("txt.txt", 'A');
  queue_system = msgget(key, 0666);  // получаем идентификатор очереди
  if (queue_system == -1)  // Очереди не существует
  {
     printf("Server is not running!\n", queue_system);
     return EXIT_FAILURE;
  }
  while(1){
    i = 0;
    printf("Please, type the fucking message:\n");
    while ( (i < (MAXLEN - 1)) && ((message.body[i++] = getchar()) !=  '\n') );
    message.body[i] = '\0';
    message.mtype = 2;
    char nick[] = "Nagibator3228";
    strcpy(message.nickname, nick);
    msgsnd(queue_system, &message, sizeof(message) - sizeof(long), 2);  // посылаем сообщение
}
  return EXIT_SUCCESS;
}
