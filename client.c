//
// client.c
// simple_client
//
// Created by Injae Lee on 2014. 10. 10.
// Modified by Minsuk Lee,
// Copyright (c) 2014. Injae Lee All rights reserved.
// see LICENSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define IP "127.0.0.1"
#define PORT 3000
#define WRITE_DATA "!dlroW olleH"

int main()
{
    int ret = -1;
    int clientSock;
    struct sockaddr_in serverAddr;

    if ((clientSock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        goto leave;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP);
    serverAddr.sin_port = htons(PORT);

    if ((ret = connect(clientSock,(struct sockaddr*)&serverAddr,
                       sizeof(serverAddr)))) {
        perror("connect");
        goto error;
    }

    if ((ret = send(clientSock, WRITE_DATA, sizeof(WRITE_DATA), 0)) <= 0) {
        perror("send");
        ret = -1;
    } else
        printf("Wrote '%s' (%d Bytes)\n", WRITE_DATA, ret);

error:
    close(clientSock);
leave:
    return ret;
}

