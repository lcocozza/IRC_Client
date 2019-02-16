#ifndef SYS_INCL_H
#define SYS_INCL_H

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <ncurses.h>
#include <panel.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define BUFFSIZE 1024
#define MSGSIZE 1000
#define PSDSIZE 24

typedef int SOCKET;

#endif
