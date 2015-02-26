all: client server
client:
	gcc -o client.exe client.c client_ipc.c client_util.c prj2.c -lrt
server:
	gcc -o server.exe server.c server_util.c server_ipc.c prj2.c -lrt
clean:
	rm *.exe *.o
