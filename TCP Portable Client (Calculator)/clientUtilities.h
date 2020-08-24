#ifndef TCP_PORTABLE_CLIENT__CALCULATOR__CLIENTUTILITIES_H
#define TCP_PORTABLE_CLIENT__CALCULATOR__CLIENTUTILITIES_H
#endif //TCP_PORTABLE_CLIENT__CALCULATOR__CLIENTUTILITIES_H

#include "clientHeader.h"

void error(char *msg, int errcode);
void dataInput(char hostname[], int *portNumber);
void menu(int clientSocket);
void sendCommand(int clientSocket, char choice);
void getConfirmation(int clientSocket);
void getSendData(int clientSocket);
void getResult(int clientSocket);

void error(char *msg, int errcode){
    printf("%s: %s", msg, strerror(errcode));
    exit(1);
}

void dataInput(char hostname[], int *portNumber){
    printf("Inserire hostname: ");
    scanf("%s", hostname);
    printf("Inserire numero di porta: ");
    scanf("%d", portNumber);
}

void menu(int clientSocket){
    int result = 0;
    char choice = 'a';

    printf("\n\nInserire A per effettuare l'addizione\n");
    printf("Inserire S per effettuare la sottrazione\n");
    printf("Inserire M per effettuare la moltiplicazione\n");
    printf("Inserire D per effettuare la divisione\n");
    printf("Inserire Q per terminare la connessione\n\n");

    do {
        printf("Inserire un comando: ");
        scanf("%s", &choice);
        choice = tolower(choice);

        sendCommand(clientSocket, choice);
        getConfirmation(clientSocket);
        getResult(clientSocket);
    } while(choice != 'q' );

}

void sendCommand(int clientSocket, char command){
    int result = 0;

    switch (command) {
        case 'a' :
            result = send(clientSocket, "a", 2, 0);
            if(result < 0)
                error("Message not sent: ", result);
            break;
        case 's':
            result = send(clientSocket, "s", 2, 0);
            if(result < 0)
                error("Message not sent: ", result);
            break;
        case 'm':
            result = send(clientSocket, "m", 2, 0);
            if(result < 0)
                error("Message not sent: ", result);
            break;
        case 'd':
            result = send(clientSocket, "d", 2, 0);
            if(result < 0)
                error("Message not sent: ", result);
            break;
        case 'q':
            result = send(clientSocket, "b", 2, 0);
            if(result < 0)
                error("Message not sent: ", result);
            break;
        default :
            result = send(clientSocket, "x", 2, 0);
            if(result < 0)
                error("Message not sent: ", result);
            break;
    }
}

void getConfirmation(int clientSocket){
    int result = 0;
    char buffer[BUFFERSIZE];
    memset(buffer, 0, sizeof(buffer));

    result = recv(clientSocket, buffer, sizeof(buffer),0);
    if (result < 0)
        error("Error receiving message", result);

    printf("\n%s\n",buffer);
    getSendData(clientSocket);
}

void getSendData(int clientSocket){
    int a = 0;
    int b = 0;
    char buf[256];

    printf("Inserire il primo intero: ");
    scanf("%d",&a);
    printf("Inserire il secondo intero: ");
    scanf("%d",&b);

    memset(&buf, 0, sizeof(buf));
    itoa(a, buf, 10);
    send(clientSocket, buf, sizeof(buf), 0);
    memset(&buf, 0, sizeof(buf));
    itoa(b, buf, 10);
    send(clientSocket, buf, sizeof(buf), 0);
}

void getResult(int socket){
    char buf[256];
    int res = 0;

    memset(&buf, 0, sizeof(buf));
    recv(socket, buf, sizeof(buf), 0);
    printf("Il risultato e: %s\n\n", buf);
}
