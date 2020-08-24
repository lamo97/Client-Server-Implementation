#include "clientHeader.h"
#include "clientUtilities.h"

int main(int argc, char* argv[]){
    int clientSocket = 0;
    int portNumber = 0;
    int result = 0;

    char buffer[BUFFERSIZE];
    char hostname[BUFFERSIZE];
    struct sockaddr_in serverInfo;
    struct hostent *server;

#ifdef WIN32
    WSADATA wsaData;
    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result < 0)
        error("Error at WSAStartup", result);
#endif

    dataInput(hostname, &portNumber);

    server = gethostbyname(hostname);

    memset(&serverInfo, 0, sizeof(serverInfo));

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr = *((struct in_addr*)server->h_addr_list[0]);
    serverInfo.sin_port = htons(portNumber);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0)
        error("Error at socket initialization", result);

    result = connect(clientSocket, (struct sockaddr*) &serverInfo, sizeof(serverInfo));
    if(result < 0)
        error("Error conneting to server", result);
    else
        printf("Connection established!");

    menu(clientSocket);
}
