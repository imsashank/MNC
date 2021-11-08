#include "../include/logger.h"
#include "../include/global.h"
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>


struct clinetSide{
    char* ip;
    int fd;
    char* host;
    int cstatus;
    int bstatus;
    int msgrecv;
    int msgsent;
    int port;
    int id_list;
    struct client* next;
};
