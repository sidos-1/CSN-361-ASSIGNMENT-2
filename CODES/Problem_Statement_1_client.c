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
        bzero(msg,sizeof(msg));
        c = 0;
        printf("Client : ");
        while ((msg[c++] = getchar()) != '\n') 
            ;

        // printf("Client : %s\n", msg);

        send(sock, msg, sizeof(msg) - 1,0);

        bzero(msg,sizeof(msg));
        recv(sock, msg, sizeof(msg), 0) ;
        printf("Server :%s\n", msg);
        if (strncmp("exit", msg, 4) == 0) 
        { 
            printf("Client Exit...\n"); 
            break; 
        } 
        
    }
}

int main()
{
    // char *file = argv[1] ;

    const char* name = "localhost";
	const int server_port = PORT;

    int client_socket, connection;
    struct sockaddr_in server, client ;
    int set_soc = 1;

    client_socket = socket(AF_INET, SOCK_STREAM, 0) ;   // protocol will decided by the machine itself
        
    if(client_socket == -1)
    {
        printf("Error in socket Creation\n");
        return 0;
    } 

    bzero(&client, sizeof(client));

    client.sin_family = AF_INET;
	inet_pton(AF_INET, name, &client.sin_addr);  //  creates binary representation of server name and stores it as sin_addr
    client.sin_port = htons(PORT); // // will convert into required format


    
    if(connect(client_socket, (struct sockaddr*)&client, (socklen_t)(sizeof(client))))  // establishing connection between client and server
    {
        printf("Error in connect()\n");
        return 0;
    }

    printf("Type \"exit\" for exiting the chat (from server)\n" ) ;
    chat(client_socket) ; // Function for chatting 

    close(client_socket);

    return 0;
}