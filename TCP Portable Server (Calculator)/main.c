#include "serverHeader.h"
#include "serverUtilities.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main (int argc, char* argv[]){
    int serverSocket = 0;
    int newSocket = 0;
    int result = 0;
    int portNumber = 0;

    struct sockaddr_in serverInfo, clientInfo;

    char buffer[BUFFERSIZE];
    char command[10];
    portNumber = DEFAULTPORT;

#ifdef WIN32
    WSADATA wsaData;
    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result<0)
        error("Error at WSAStartup", result);
#endif

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        WSACleanup();
        error("Error at socket initialization", result);
    }
    else{
        printf("Socket initialized!\n");
    }

    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(portNumber);
    serverInfo.sin_addr.s_addr = INADDR_ANY;

//  setServerInfo(&serverInfo, portNumber);
    result = 0;
    result = bind(serverSocket, (struct sockaddr*) &serverInfo, sizeof(serverInfo));
    if (result < 0){
        error("Error at binding", result);
    }

    int clientSize = sizeof(clientInfo);

    while (1) {
        result = listen(serverSocket, 5);
        if (result < 0){
            WSACleanup();
            error("Error when listening", result);
        }

        memset(&clientInfo, 0, clientSize);

        newSocket = accept(serverSocket, (struct sockaddr*) &clientInfo, &clientSize);

        if(newSocket < 0) {
            WSACleanup();
            error("Error establishing connection", newSocket);
        }
        else
            printf("Connection established!\n");

        while(1){
            memset(&buffer, 0, sizeof(buffer));
            result = recv(newSocket, buffer, sizeof(buffer),0);
            if(result < 0){
                WSACleanup();
                error("Error reading from socket", result);
            }

            sendConfirmation(newSocket, buffer);
            compute(newSocket,buffer);
        }
    }
}
