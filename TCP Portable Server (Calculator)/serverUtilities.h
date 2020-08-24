#ifndef TCP_PORTABLE_SERVER__CALCULATOR__SERVERUTILITIES_H
#define TCP_PORTABLE_SERVER__CALCULATOR__SERVERUTILITIES_H

#endif //TCP_PORTABLE_SERVER__CALCULATOR__SERVERUTILITIES_H

#include "serverHeader.h"

void error(char *msg, int errcode);
void sendConfirmation(int serverSocket, char buffer[]);
void compute(int socket, char buffer[]);

void error(char *msg, int errcode) {
    printf("%s: %s", msg, strerror(errcode));
    exit(1);
}

void sendConfirmation(int serverSocket, char buffer[]) {
    int result = 0;

    if (strcmp(buffer, "a") == 0) {
        result = send(serverSocket, "ADDIZIONE", 9, 0);
        if (result < 0)
            error("Message not sent: ", result);
    }
    else if ((strcmp(buffer, "s") == 0)) {
        result = send(serverSocket, "SOTTRAZIONE", 11, 0);
        if (result < 0)
            error("Message not sent: ", result);
    }
    else if ((strcmp(buffer, "m") == 0)) {
        result = send(serverSocket, "MOLTIPLICAZIONE", 15, 0);
        if (result < 0)
            error("Message not sent: ", result);
    }
    else if ((strcmp(buffer, "d") == 0)) {
        result = send(serverSocket, "DIVISIONE", 9, 0);
        if (result < 0)
            error("Message not sent: ", result);
    }
    else if ((strcmp(buffer, "q") == 0)) {
        result = send(serverSocket, "BYE", 3, 0);
        if (result < 0)
            error("Message not sent: ", result);
    }
    else {
        result = send(serverSocket, "SCONOSCIUTO", 11, 0);
        if (result < 0)
            error("Message not sent: ", result);
    }
}

void compute(int socket, char buffer[]) {
    char data[2];
    int result = 0;
    int a = 0;
    int b = 0;
    int res = 0;

    memset(&data, 0, sizeof(data));
    recv(socket, data, sizeof(data), 0);
    a = atoi(data);

    memset(&data, 0, sizeof(data));
    recv(socket, data, sizeof(b), 0);
    b = atoi(data);

    if (strcmp(buffer, "a") == 0) {
        res = a + b;
        memset(&data, 0, sizeof(data));
        itoa(res, data, 10);
        printf("da mandare: %s", data);
        send(socket, data, sizeof(data), 0);
    }
    else if ((strcmp(buffer, "s") == 0)) {
        res = a - b;
        memset(&data, 0, sizeof(data));
        itoa(res, data, 10);
        send(socket, data, sizeof(data), 0);
    }
    else if ((strcmp(buffer, "m") == 0)) {
        res = a * b;
        memset(&data, 0, sizeof(data));
        itoa(res, data, 10);
        send(socket, data, sizeof(data), 0);
    }
    else if ((strcmp(buffer, "d") == 0)) {
        res = a / b;
        memset(&data, 0, sizeof(data));
        itoa(res, data, 10);
        send(socket, data, sizeof(data), 0);
    }
}
