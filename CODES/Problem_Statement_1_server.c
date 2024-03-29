#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PORT 8080 // we can use any valid port number

void chat(int sock)
{
    char msg[128] ;
    int c = 0;

    while(1)
    {
        bzero(msg,128);
        recv(sock, msg, sizeof(msg), 0) ;
        printf("Client : %s\n", msg);
        bzero(msg,128);
        c = 0;
        printf("Server : ");
        while ((msg[c++] = getchar()) != '\n') 
            ;

        send(sock, msg, sizeof(msg),0);

        if (strncmp("exit", msg, 4) == 0) 
        { 
            printf("Server Exit...\n"); 
            break; 
        } 
    }
}

int main()
{
    // char *file = argv[1] ;
    int server_socket, connection;
    struct sockaddr_in server, client ;
    int set_soc = 1;
    server_socket = socket(AF_INET, SOCK_STREAM, 0) ;   // protocol will decided by the machine itself

    if(server_socket == -1)
    {
        printf("Error in socket Creation\n");
        return 0;
    }

    bzero(&server, sizeof(server));



    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &set_soc, sizeof(set_soc))) 
    { 
        printf("setsockopt error\n") ; 
        return 0;; 
    }

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT) ; // will convert into required format
    server.sin_addr.s_addr = htonl(INADDR_ANY) ; // no address is required since on same machine



    if(bind(server_socket, (struct sockaddr*)&server, sizeof(server))!=0)
    {
        printf("Error in binding\n");
        return 0;;
    }


    if(listen(server_socket, 5)!=0)
    {
        printf("Error in listening\n");
    }


    int len = sizeof(client);

    connection = accept(server_socket, (struct sockaddr*)&client, &len) ; // establishing connection between client and server

    if(connection < 0)
    {
        printf("Error in accept()\n");
        return 0;
    }

    
    printf("Type \"exit\" for exiting the chat (from server)\n" ) ;
    chat(connection) ; // Function for chatting 

    close(server_socket);

    return 0;
}