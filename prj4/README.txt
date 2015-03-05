FILES:
    For each protocol, there are a PROTOCOL_client.c file, a PROTOCOL_server.c file.
    There is also a prj4.h file which includes all the headers needed for the entire project, and a prj4_util.c which includes functions used for both socket types, such as valid_command, read_file, etc.
	After being compiled, there are for executable files, a client / server for each socket type. 

IMPLEMENTATION:
1)  Working flow:
There are two pair of client/server programs each of which is for a corresponding socket type of the project, however, they implement similar model of working flow.
a)	TCP programs:
    First the server should be running on one host (terminal). It will open and bind the parent process to a “listening” socket which is used for listening incoming connection of clients. 
    Secondly, after the client starts running on another host (terminal), it will connect to the server program, validate user input, and send the user request to the server.
    Thirdly, when the server accepts the client’s connection request, then forks a new child process to serve the requests of that client, meanwhile the parent process goes back to listen to the listening socket.
    At last, the server’s child process will do the operations according to the client’s requests, and send the result back. After that, the client can finally read the result sent back by the server and show it on standard output.
b)	UDP programs
The working flow of UDP programs are fairly similar to TCP programs, except that the server does not “listen()” to the socket for connection, also the client and the server do not keep a connection in between since UDP is connectionless. They just send and receive data to the corresponding socket. Besides that, the synchronization is the same.
2)  Data
    The data written to the sockets by the client is always a file operation command, which is, either read or delete plus a potentially valid file name.
    The data written to the sockets by the server is of one kind of described below:
	a)  If the command is read, and the file exists, the data is the content of the file;
	b)  If the command is read, but the file name is missing, the data is the information about the missing / wrong file name;
	c)  If the command is delete, and the file exists, the server would delete the file and the data passed back to client is a successful message;
	d)  If the command is delete, and the file is missing, the server would write back a message about the missing file.

USAGE:
1)  To compile, type make; to clean up, type make cleanall.
2)  There are four executables, each pair of client / server program is for the corresponding protocol of the project. 
3)  The command format is: 
	a)  [read | delete] [filename] -- to read or delete a file
	b)  [exit]  --	cleanup environment and exit the programm
