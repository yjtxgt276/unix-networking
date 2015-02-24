all:
sv:
	gcc sv_util.c sv_client.c sv_server.c prj3_util.c -o sv.exe
px:
	gcc px_util.c px_client.c px_server.c prj3_util.c -o px.exe -lpthread -lrt
svclient:
	gcc sv_util.c sv_client.c -o sv_client.exe
svserver:
	gcc sv_util.c sv_client.c -o sv_server.exe
cleanall:
	rm *.out *.exe *.o
