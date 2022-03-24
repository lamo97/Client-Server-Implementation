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
   int cSocket, result, serverSize, portNumber;
    char inBuffer[BUFFERSIZE];
    char outBuffer[BUFFERSIZE];
    char hostName[BUFFERSIZE];
    struct sockaddr_in serverAddress;
    struct hostent *serverInfo;

    //inizializzazione WSADATA
#ifdef WIN32
    WSADATA WSAData;
    result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if(result<0){
        WSACleanup();
        error("Error at WSAStartup()!", result);
    }
#endif

    //inserimento da tastiera dati connessione
    printf("Inserire Hostname e Port Number\n");
    printf("Hostname: ");
    scanf("%s", hostName);
    printf("Port Number: ");
    scanf("%d", &portNumber);

    //hostname to ip address
    serverInfo = gethostbyname(hostName);

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_addr = *((struct in_addr *) serverInfo->h_addr_list[0]);

    //inizializzazione struttura sockaddr_in
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);

    //creazione socket
    cSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(cSocket<0){
        WSACleanup();
        error("Error creating socket!", cSocket);
    }

    //invio primo messaggio
    serverSize = sizeof(serverAddress);
    result = sendto(cSocket, "Connessione...", 14, 0, (struct sockaddr*) &serverAddress, serverSize);
    if(result<0){
        WSACleanup();
        error("Error sending message!", result);
    }



}

void error(char *msg, int errcode) {
    printf("%s: %d", msg,errcode);
    exit(1);
}
