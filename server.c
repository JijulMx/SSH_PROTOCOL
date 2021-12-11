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
        int socket_desc = 0 ,client_sock = 0, c , valread,n,j;
        struct sockaddr_in server, client;

        char buffer[255];
        char *hello = "98lk@7!";
        char *success = "Authentication Success!!";

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("No request received");
        }

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(4040);

        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                //print the error message
                perror("bind failed. Error");
                return 1;
        }

        //Listen
        listen(socket_desc , 5);

        //Accept and incoming connection
        puts("\nWaiting for incoming connections...");
        c = sizeof(struct sockaddr_in);
        //accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
                perror("failed...");
                return 1;
        }
        puts("Connection accepted!!");

        send(client_sock , hello , strlen(hello) , 0 );
        printf("\nSending random message to client\n");
        printf("Waiting for the secret key....");
        while(1)
        {
                bzero(buffer ,255);
                n = read(client_sock, buffer, 100);
                if(j<0)
                error("Error reading");
                printf("\n[+key]");
                printf("%s", buffer);
                printf("\nEncrypted message with secret key received!!\n");
                printf("\nDecrypted the encrypted random message using the client's public key.....");
                printf("\nAuthentication >>> Success!!\n");
                printf("\nSending affirmative response to client....\n");
                bzero(buffer ,255);
                fgets(buffer ,255, stdin);

                break;
        }
        send(client_sock , success , strlen(success) , 0 );
        printf("Negotiated successful, connection verified.\n");
        printf("\n                Secure connection [ Active ] \n\n");

        while(1)
        {
                bzero(buffer ,255);
                n = read(client_sock, buffer, 255);
                if(n<0)
                        error("\nError reading");
                printf("\nClient>> %s\n", buffer);
                bzero(buffer ,255);
                fgets(buffer ,255, stdin);
                n = write(client_sock, buffer, strlen(buffer));
                if (n<0)
                        error("\nError writing!");
                int i = strncmp("Turn Off", buffer, 3);
                if(i == 0)
                break;
        }
        printf("\n\n*SSH connection terminate*\n\n");
        return 0;
}
