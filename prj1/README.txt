1. To compile, simply type "make", this will generate two executable files.
2. To clean up, type "make clean", this will remove the executable files and the shared "ipc" file.
3. To run the application, run "client.exe", and it will show you the command format.
4. The executable "server.exe" cannot be run by itself, it is supposed to be run by the client, client.exe.
5. The implemented operations are "read" and "delete". "read" command will display the specified file's content, and the "delete" command just simply deletes the specified file.
6. There is a testfile in the folder along with the code for testing the application.
7. To check the states of the processes, simply use "ps -le | grep exe".
