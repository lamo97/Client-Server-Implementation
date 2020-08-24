#ifndef TCP_PORTABLE_SERVER__CALCULATOR__SERVERHEADER_H
#define TCP_PORTABLE_SERVER__CALCULATOR__SERVERHEADER_H

#endif //TCP_PORTABLE_SERVER__CALCULATOR__SERVERHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#define BUFFERSIZE 256
#define DEFAULTPORT 8080



