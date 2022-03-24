#include <stdio.h>

#if defined WIN32

#include <winsock.h>

#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#define BUFFERSIZE 256

void error(char *msg, int errcode);

int main() {
    int sSocket, result, clientSize;
    char inBuffer[BUFFERSIZE];
    char outBuffer[BUFFERSIZE];
    char *hostName;
    char ipAddress[BUFFERSIZE];
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    struct hostent *clientInfo;

    //inizializzazione WSADATA
#ifdef WIN32
    WSADATA WSAData;
    result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if(result<0){
        WSACleanup();
        error("Error at WSAStartup()!", result);
    }
#endif

    //inizializzazione struttura serverAddress
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    //inizializzazione socket
    sSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(sSocket<0){
        WSACleanup();
        error("Error creating socket!", sSocket);
    }

    //binding
    result = bind(sSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if(result<0){
        WSACleanup();
        error("Error at binding!", result);
    }

    listen(sSocket, 5);

    //ricezione primo messaggio
    memset(&inBuffer, 0, BUFFERSIZE);
    clientSize = sizeof(clientAddress);

    result = recvfrom(sSocket, inBuffer, BUFFERSIZE, 0, (struct sockaddr *) &clientAddress, &clientSize);
    if(result<0){
        WSACleanup();
        error("Error receiving message!", result);
    }

    //info sul client
    clientInfo = gethostbyaddr((char *) &clientAddress.sin_addr, 4, AF_INET);
    hostName = clientInfo -> h_name;
    strcpy(ipAddress, inet_ntoa(*((struct in_addr *) clientInfo->h_addr_list[0])));

    printf("Messaggio ricevuto da: %s (%s)", hostName, ipAddress);

    printf("\n%s", inBuffer);

}

void error(char *msg, int errcode) {
    printf("%s: %d", msg,errcode);
    exit(1);
}
