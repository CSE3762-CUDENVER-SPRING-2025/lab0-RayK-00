@Lab: 0
@Description: C implementation of a simple server and client programs utilizing a UDP
connection. Client connects to a server, sends a message, and receives a reply from
the server.
@files: server.c client.c Makefile.txt README.txt
@section: CSCI 3762 002
@due: 1/28/25
@author: Ray Khan 
@requirements: GCC or any C compiler, Unix-based system (Linux/MacOS)

@Instructions:
	-Ensure server.c, client.c, and Makefile.txt are within the desired testing directory.
	-Run the '$ make' command (or alternatively '$ make all') on the command line to compile both programs.
	-Can run the '$ make clean' command to clean any previous server/client executables.
	
	@Server
	-Once the server has been compiled:
		-Start the server via command line, ensure to enter the desired port number:$ ./server [port number]
	-The server now waits continuously for a connection and message.

	@Client
	-Once the client has been compiled:
		-Initiate the client via command line, ensure to enter the servers IP and the configured port number,
		separated by a single space.
		-$ ./client [server IP] [port number]
		-Client closes once server message has been received.