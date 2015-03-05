#include "prj4_util.h" 
int main(int argc, char** argv){
	int sockfd, newfd;  
	struct addrinfo hints, *servinfo, *rp;
	struct sockaddr_storage peer_addr; 
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN], input[MAX_LEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // wildcard addr for server
	if ((rv = getaddrinfo(NULL, TCP_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
/*bind to a socket*/
	for(rp = servinfo; rp != NULL; rp = rp->ai_next) {
		if ((sockfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}
		break;
	}
	if (rp == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	freeaddrinfo(servinfo); 
/*listen*/
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	printf("server: waiting for connections...\n");
	while(1) {
/*accept*/
	    sin_size = sizeof peer_addr;
	    newfd = accept(sockfd, (struct sockaddr *)&peer_addr, &sin_size);
	    if (newfd == -1) {
	    	perror("accept");
	    	continue;
	    }
	    inet_ntop(peer_addr.ss_family,
		get_in_addr((struct sockaddr *)&peer_addr),s, sizeof s);
	    printf("server: got connection from %s\n", s);
	    if (!fork()) { 
		char buf[MAXDATASIZE];
		while(1){
	    	close(sockfd); 
		/*read cmd*/
		memset(input,0,MAX_LEN);
		if(recv(newfd,input,MAX_LEN,0)==-1){
			perror("recv");
			return 1;
		}
		/*process request*/
		process_cmd(input,buf);	
		/*send back result*/
	    	if (send(newfd, buf, MAXDATASIZE-1, 0) == -1){
	    		perror("send");
			return 1;
		}
		printf("sent\n");
		    memset(buf,0,MAXDATASIZE);
		}
	    	close(newfd);
	    	exit(0);
	    }
	    close(newfd);  
	}
	return 0;
}


