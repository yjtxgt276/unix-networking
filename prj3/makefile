all: sv px
sv:
	gcc sv_util.c sv_client.c sv_server.c prj3_util.c -o sv.exe
px:
	gcc px_util.c px_client.c px_server.c prj3_util.c -o px.exe -lpthread -lrt
cleanall:
	rm *.out *.exe *.o
