/*
@file server.c
@brief Lab 0: Server side implementation for handling a client request. 
The server expects a command line argument with the desired port. Server 
binds to specified port and any available IP, creates the socket for communication,
and waits for client response. Server sends a response back.
@author Ray Khan
@section CSCI 3762 002
@due 1/28/2025
@enviornment Text-editor (VS CODE); Compiled and tested on two separate
csegrid linux server nodes.
*/

//Header files, including network libraries.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


/*
@Function name: receive_data()
@Param: int sockd
@Returns: none
@Description: Function to receive data from a client. The function
takes in the socket descriptor (int) as a parameter and prepares for 
client response. It will notify the user if any error occurs. The server
then sends the client a response message notifying a successful connection.
*/

void receive_data(int sockd){
    char client_reply[250];         //Buffer to store client message.
    struct sockaddr_in fromAddr;    //Prepare to hold address information.
    socklen_t fromAddr_len = sizeof(struct sockaddr_in);
    
    //Receives Data from Client. Keeps track of client address.
    int check = recvfrom(sockd, &client_reply, sizeof(client_reply), 0, (struct sockaddr*)&fromAddr, &fromAddr_len);
    if (check < 0){ //Error handling.
        perror("Error receiving data.");
        exit(1);
    }
    
    //str_buffer[check] = '\0'; //Null terminate string buffer
    
    printf("Received message from client: %s\n", client_reply); //Displays client message to server.
    
    //Sends reply back to client at the same address.
    char server_reply[] = "Welcome to CSE5462."; //Server reponse to client.
    int sent_check = sendto(sockd, &server_reply, sizeof(server_reply), 0, (struct sockaddr*)&fromAddr, fromAddr_len);
    if (sent_check < 0){
        perror("Error sending reply.");
        exit(1);
    }
    printf("Responded with: %s\n", server_reply); //Displays server message to client.
}

/* Main driver function */
int main(int argc, char *argv[]){   //Program expects command line arguments.
     if (argc !=2){                 //Notifies the user if command line arguments are not met.
        printf("Error. Please ensure you are entering a port number.\n");
        exit(1);
    }
    int port_num = strtol(argv[1], NULL, 10);   //Convert command line argument to int.
    
    //Prepares to hold server information and initializes the server.
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_num);      //Ensures to convert port number to appropriate data type.
    serverAddr.sin_addr.s_addr = INADDR_ANY;    //Any available address.
    
    //Creates the socket. Stores return code for error check.  
    int sockd = socket(AF_INET, SOCK_DGRAM, 0); //Utilizes datagram/UDP connection.
    if (sockd < 0){ 
        printf("Error creating socket.\n");
        exit(1);
    }

    //Binds the socket to the address and port number stored in the struct. Notifies if bind failed.
    int bindCheck = bind(sockd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bindCheck < 0){ 
        printf("Error binding to socket.\n");
        exit(1);
    }  

    //Loop to handle multiple client requests. 
    while (1) {
        //Receives data by socket via recieve_data function call.
        receive_data(sockd); 
    }
    //Closes the socket connection.
    close(sockd);
    //Exits program.
    return 0;
}