#include "prj4_util.h"

int main(void)
{
    int sockfd,rv,numbytes;
    struct addrinfo hints, *servinfo, *rp;
    struct sockaddr_storage peer_addr;
    char buf[MAXDATASIZE], s[INET6_ADDRSTRLEN],input[MAX_LEN];
    socklen_t addr_len;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;    //wildcard 
    if ((rv = getaddrinfo(NULL, UDP_PORT, &hints, &servinfo)) != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	return 1;
    }
    /*bind a socket*/
    for(rp = servinfo; rp != NULL; rp = rp->ai_next) {
    	if ((sockfd = socket(rp->ai_family, rp->ai_socktype,
		rp->ai_protocol)) == -1) {
	    perror("socket");
	    continue;
	}
	if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == -1) {
	    close(sockfd);
	    perror("bind");
	    continue;
	}
	break;
    }
    if (rp == NULL) {
	fprintf(stderr, "failed to bind socket\n");
	return 2;
    }
    freeaddrinfo(servinfo);
    while(1){
	printf("server: waiting to recvfrom...\n");
    /*recv request*/
	addr_len = sizeof peer_addr;
	if ((numbytes = recvfrom(sockfd, input, MAX_LEN, 0,
	    (struct sockaddr *)&peer_addr, &addr_len)) == -1) {
	    perror("recvfrom");
	    continue;
	}
	printf("server: got packet from %s\n",
	    inet_ntop(peer_addr.ss_family,
		    get_in_addr((struct sockaddr *)&peer_addr),s, sizeof s));
	printf("server: packet is %d bytes long\n", numbytes);
	/*process request*/
	process_cmd(input,buf);
	/*send back result*/
	if((numbytes=sendto(sockfd,buf,MAXDATASIZE,0,
		(struct sockaddr*)&peer_addr,addr_len)) == -1){
	    perror("sendto");	
	    continue;
	}
	printf("sent\n");
	memset(buf,0,MAXDATASIZE);
    }
    close(sockfd);
    return 0;
}

