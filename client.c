#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>


void error(const char *msg)
{
        perror(msg);
        exit(0);
}

int main(int argc , char *argv[])
{
        int socket_desc = 0,s,n,j;
        struct sockaddr_in server;
        int valread;
        char buffer[256];

        //Accept and incoming connection
        puts("\nSending request to server...");
        s = sizeof(struct sockaddr_in);

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not send request");
        }

        server.sin_addr.s_addr = inet_addr("192.168.56.103");
        server.sin_family = AF_INET;
        server.sin_port = htons( 4040 );

        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("connection error\n");
                return 1;
        }
        puts("Connected!!\n");

        valread = read( socket_desc , buffer, 1040);
        printf("Server : %s\n",buffer );
        printf("\nEncrypt message with secret key....\n");
        printf(">>> ");

        while(1)
        {
                bzero(buffer, 256);
                fgets(buffer,255,stdin);
                j = write(socket_desc,buffer,strlen(buffer));
                if (j<0)
                error("\nError sending!");
                printf("\nSending encrypt message with secret key to server....");
                printf("\nDecrypted ongoing.....\n");
                bzero(buffer, 256);

                break;
        }
        valread = read( socket_desc , buffer, 1040);
        printf("[%s]\n",buffer );
        printf("Negotiated successful, connection verified.\n");
        printf("\n>>> Exchange data between client and server protected <<<\n");
        printf("\n                Secure connection [ Active ] \n\n");

        while(1)
        {
        bzero(buffer, 256);
        fgets(buffer,255,stdin);
        n = write(socket_desc,buffer,strlen(buffer));
        if (n<0)
                error("\nError writing!");
        bzero(buffer, 256);
        n = read(socket_desc,buffer,255);
        if (n<0)
                error("\nError reading!");
        printf("\nServer>>%s\n",buffer);
        int i = strncmp("Turn Off", buffer, 3);
        if(i == 0)
                break;
        }
        printf("\n\n*SSH connection terminate*\n\n");
        return 0;
}
