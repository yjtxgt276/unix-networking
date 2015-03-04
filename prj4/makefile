all: udp tcp
udp: udp_client udp_server
udp_client:
	gcc -o udp_client.exe udp_client.c
udp_server:
	gcc -o udp_server.exe udp_server.c
tcp: tcp_server tcp_client
tcp_server:
	gcc -o tcp_server.exe tcp_server.c
tcp_client:
	gcc -o tcp_client.exe tcp_client.c
cleanall:
	rm *.exe *.out
