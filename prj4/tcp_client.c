#include "prj4_util.h"

int main(int argc, char** argv){
    int sockfd, numbytes;  
    char buf[MAXDATASIZE], input[MAX_LEN];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(argv[1], TCP_PORT, &hints, &servinfo)) != 0) {
    	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    	return 1;
    }
/*make a socket, connect to it*/
    for(p = servinfo; p != NULL; p = p->ai_next) {
    	if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
    	    perror("client: socket");
	    continue;
    	}
	if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
	    close(sockfd);
	    perror("client: connect");
	    continue;
	}
	break;
    }
    if (p == NULL) {
	fprintf(stderr, "client: failed to connect\n");
	return 2;
    }
    else{
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
		s, sizeof s);
	printf("client: connecting to %s\n", s);
	printf("client: connected\n");
    }
    freeaddrinfo(servinfo); 
/*infi loop*/
    while(1){
/*validate user input*/
	printf("client: enter your command:"); 
	memset(input,0,MAX_LEN);
	if(fgets(input, MAX_LEN-1, stdin) == NULL){
	    error("read");	
	    continue;
	}
	input[MAX_LEN] = '\0';
	if((rv = valid_cmd(input)) == -1)
	    continue;
	else if(rv == ALL_EXIT){
	    exit(0);
	}
/*send command to server*/
	if(send(sockfd,input,sizeof(input),0)==-1){
		perror("send");
		continue;
	}
/*get result from server*/
	memset(buf,0,MAXDATASIZE);
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
            exit(1);
	}
        buf[numbytes] = '\0';
	printf("client: received form server:\n%s\n",buf);
/*display result*/
    
    }
    close(sockfd);
    return 0;
}

