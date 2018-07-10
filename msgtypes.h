#ifndef MSG_TYPES
#define MSG_TYPES

#define MAXLEN 512

struct msg_t  
{
   long mtype;
   char nickname[64];
   char body[MAXLEN];
};

#endif
