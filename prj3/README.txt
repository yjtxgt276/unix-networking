FILES:
    For each ipc mode, there are a MODE_client.c file, a MODE_server.c file, and a MODE_util.c file, as well as their corresponding header files. 
    There is also a prj3.h file which includes all the headers needed for the entire project, and a prj3_util.c which includes functions used for both ipc modes, such as valid_command, read_file, etc.

IMPLEMENTATION:

1)  Working flow:
    There are two different programs each of which is for a different ipc mode of the project, however, they implement similar model of working flow.
    First the client will set up environment needed for the program, such as creating semaphore and shared memory / memory mapped file.
    Secondly, the client will fork a process to execute the server,which will be blocked then, and the client itself continues to do its job, getting user command, validing the command, writing command to ipc object,etc.
    Thirdly, the server will unblock after the client increasing the semaphore, and decreases the semaphore to read from and write to the critical section, which is the shared memory / mapped file.
    At last, the server increases the semaphore, and the client will be awaken, and perfoms its functions, meanwhile the server blocks itself waiting for the semaphore to be increased by the client.

2)  Data
    The data writen to the shared memory / mapped file by the client is always a file operation command, that is, either read or delete plus a potentially valid file name.
    The data writen to the shared memory / mapped file by the server is of one kind of described below:
	a)  If the command is read, and the file exists, the data is the content of the file;
	b)  If the command is read, but the file name is missing, the data is the information about the missing / wrong file name;
	c)  If the command is delete, and the file exists, the server would delete the file and the data passed back to client is a successful message;
	d)  If the command is delete, and the file is missing, the server would write back a message about the missing file.

USAGE:
1)  To compile, type make; to clean up, type make cleanall.
2)  There are two executables, each for one ipc mode of the project. The px.exe	    is for POSIX, and the sv.exe is for System V.
3)  The command format is: 
	a)  [read | delete] [filename] -- to read or delete a file
	b)  [exit]  --	cleanup environment and exit the programm
