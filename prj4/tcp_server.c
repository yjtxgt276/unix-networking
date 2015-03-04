#include "prj4.h" 

#define PORT "3490"  
//TODO the port users will be connecting to

#define BACKLOG 10	 
//TODO how many pending connections queue will hold

void sigchld_handler(int s){
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void *get_in_addr(struct sockaddr *sa){
/*get address info*/
	if (sa->sa_family == AF_INET) 
	    return &(((struct sockaddr_in*)sa)->sin_addr);
	else
	    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char** argv){
	int sockfd, newfd;  // listen on sock_fd, new connection on newfd
	struct addrinfo hints, *servinfo, *rp;
	struct sockaddr_storage peer_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // wildcard addr for server
	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
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
	freeaddrinfo(servinfo); // all done with this structure
/*listen*/
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");
/*accept*/
	while(1) {  // main accept() loop
	    sin_size = sizeof peer_addr;
	    newfd = accept(sockfd, (struct sockaddr *)&peer_addr, &sin_size);
	    if (newfd == -1) {
	    	perror("accept");
	    	continue;
	    }
	    inet_ntop(peer_addr.ss_family,
		get_in_addr((struct sockaddr *)&peer_addr),s, sizeof s);
	    printf("server: got connection from %s\n", s);
	    if (!fork()) { // this is the child process
	    	close(sockfd); // child doesn't need the listener
	    	if (send(newfd, "Hello, world!", 13, 0) == -1)
	    		perror("send");
	    	close(newfd);
	    	exit(0);
	    }
	    close(newfd);  // parent doesn't need this
	}

	return 0;
}

