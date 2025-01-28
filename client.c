/*
@file client.c
@brief Lab 0: client side implementation for sending a message to a server. 
Expects two command line arguments (server IP and port number, in that order). 
The client binds to the specified address and creates the socket for communication.
The client sends a message and recieves a server reply.
@author: Ray Khan
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

/*Main driver function.*/
int main(int argc, char *argv[]){ //Utilizes command-line arguments for serverIP and port #.
    if (argc !=3){                //Notifies the user if command line arguments are not met.
        printf("Error. Please ensure you are entering in (server IP) (port number) on the command line.\n");
        exit(1);
    }
    //Variables for IP and Port number.
    char *IP = argv[1];                         //Stores command line argument for server IP.
    int port_num = strtol(argv[2], NULL, 10);   //Converts command line argument to int.

    //Prepares to hold server information and initializes the server.
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_num);      //Ensures to convert port number to appropriate byte order type.
    serverAddr.sin_addr.s_addr = inet_addr(IP); //Converts IP to appropriate format.
    
    //Creates the socket. Stores return code for error check.
    int sockd = socket(AF_INET, SOCK_DGRAM, 0); //Utilize datagram/UDP connection.
    if (sockd < 0){
        perror("Error creating socket.");
        exit(1);
    }
    
    char client_reply[] = "Hello, World!";  //Message to send to server.
    char server_reply[100];                 //Buffer to hold server response.
    socklen_t serverAddr_len = sizeof(serverAddr); 
    
    //Sends data to server. Keeps track of server info. 
    int check = sendto(sockd, client_reply, sizeof(client_reply), 0, (struct sockaddr*)&serverAddr, serverAddr_len);
    if (check < 0){
        perror("Data send failed.");
        exit(1);
    }
    //Displays message sent to server and receives reply from server.
    printf("Sent: '%s'\n", client_reply, check);
    int receive_check = recvfrom(sockd, &server_reply, sizeof(server_reply), 0, (struct sockaddr*)&serverAddr, &serverAddr_len);
    if (receive_check < 0){
        perror("Error receiving Server message.");
        exit(1);
    }
    //Displays server reply.
    printf("Received from server: '%s'\n", server_reply);
    //Closes the socket connection.
    close(sockd);
    //Exits program.
    return 0;
}