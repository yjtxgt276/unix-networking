<<<<<<< HEAD
1.Usage:
	After launching client.exe, enter in some commands in following form:
	a) <switch> <ipc>
	b) <read/delete> <filename>
	c) <exit>
	The first command should always be <switch> <ipc>, since the programs
	needs to know in which way to talk to each other.
	The in program usage message also point this out.

2.Files & functions:
	Files include: clien.c, client_ipc.c, client_util.c, server.c,
	server_ipc.c, server_util.c, prj2.c, and their corresponding headers.

	File description:
		client.c: main function for client.exe program, it sets up varibals, ipc environment, and signal handlings for the program.
		client_ipc.c: ipc relative functions for the client, including creating,setting up, etc.
		client_util.c: some utility functions for client, including input validation, sending/rcving data, etc.	
		Fucntions for servers are similarly spreaded in corresponding files.
3.Implementation:
	The parent process majorly perform the client.exe, meanwhile the child mainly performs the server.exe. 
	The parent first create all forms of ipcs needed later plus one single pipe for sending the ipc mode to server,and then fork a child to exec the server program,passing the identifiers of ipcs to the server as arguments. When the client get user input, it will send the ipc mode chosen by the user to the server first, then send the data via the ipc. 
	For the server, it checks the pipe to which the client sends the ipc
mode, then read data from specified ipc accordingly. Every time the user
switch to another ipc mode, the server need NOT to be executed again, instead
it just read data from a different ipc item.
	The server and client are synchronized via signal handling.
=======

>>>>>>> 571fda7bd2106696560489fde0829516c2b1241c
