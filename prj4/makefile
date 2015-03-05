all: udp tcp
udp: udp_client udp_server
udp_client:
	gcc -o udp_client.exe udp_client.c prj4_util.c
udp_server:
	gcc -o udp_server.exe udp_server.c prj4_util.c
tcp: tcp_server tcp_client
tcp_server:
	gcc -o tcp_server.exe tcp_server.c prj4_util.c
tcp_client:
	gcc -o tcp_client.exe tcp_client.c prj4_util.c
cleanall:
	rm *.exe *.out
