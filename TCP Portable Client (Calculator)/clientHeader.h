#ifndef TCP_PORTABLE_CLIENT__CALCULATOR__CLIENTHEADER_H
#define TCP_PORTABLE_CLIENT__CALCULATOR__CLIENTHEADER_H

#endif //TCP_PORTABLE_CLIENT__CALCULATOR__CLIENTHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#ifdef WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif


#define BUFFERSIZE 256


