all: client server
client:
	gcc -o client.exe client.c client_ipc.c client_util.c
server:
	gcc -o server.exe server.c server_util.c server_ipc.c
clean:
	rm *.exe *.o
