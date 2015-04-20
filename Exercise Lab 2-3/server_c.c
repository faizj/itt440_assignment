/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<stdlib.h>

 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    //char tokens;
    char *saveptr;
    char *str_operator, *str_value_a, *str_value_b;
    int a,b,total;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
	/*
	p = strtok(client_message, " ");
	if(p != NULL)
	{
		strcpy(str_operator,p);
		p = strtok (NULL, " ");
		if(p != NULL)
		{
			strcpy(str_value_a,p);
			p = strtok (NULL,p);
			if(p != NULL)
			{
				strcpy(str_value_b,p);
			} 
		}
	}
	*/
	//str_value_a = strtok(client_message, " ");
	//str_value_b = strtok(client_message, " ");

	str_operator = strtok_r(client_message, " ", &saveptr);
	str_value_a = strtok_r(NULL, " ", &saveptr);
	str_value_b = strtok_r(NULL, " ", &saveptr);

	
	a = atoi(str_value_a);
	b = atoi(str_value_b);

	if(strcmp(str_operator, "ADD") == 0)
	{
		total = a+b;
	}
	else if(strcmp(str_operator, "SUBTRACT") == 0)
	{
		total = a-b;
	}
	else
	{
		total = 99;
	}
	sprintf(client_message, "%d", total);

	//printf("value a: %s",str_value_a);

        write(client_sock , client_message , strlen(client_message));
	//write(client_sock , str_operator , strlen(str_operator));
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}
