all: client server
client:
	gcc -o client.exe client.c ipc_util.c client_util.c
server:
	gcc -o server.exe server.c server_util.c
clean:
	rm *.exe *.o
