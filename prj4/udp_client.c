#include "prj4_util.h"

int main(int argc, char** argv){
	int sockfd,rv,numbytes;
	struct addrinfo hints, *servinfo, *rp;
	char input[MAX_LEN], buf[MAXDATASIZE];
	if (argc != 2) {
		fprintf(stderr,"usage: %s hostname\n",argv[0]);
		exit(1);
	}
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	if ((rv = getaddrinfo(argv[1], UDP_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	/*bind to a socket*/
	for(rp = servinfo; rp != NULL; rp = rp->ai_next) {
		if ((sockfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		break;
	}
	if (rp == NULL) {
		fprintf(stderr, "failed to bind socket\n");
		return 2;
	}
	while(1){
	/*validate user input*/
	    printf("client: enter your command:"); 
	    memset(input,0,MAX_LEN);
	    if(fgets(input, MAX_LEN-1, stdin) == NULL){
		error("read");	
		continue;
	    }
	    input[MAX_LEN-1] = '\0';
	    if((rv = valid_cmd(input)) == -1)
		continue;
	    else if(rv == ALL_EXIT){
		exit(0);
	    }
	    /*send to server*/
	    if ((numbytes = sendto(sockfd, input, MAX_LEN, 0,
			 rp->ai_addr, rp->ai_addrlen)) == -1) {
		perror("sendto");
		continue;
	    }
	    /*recv back*/
	    if((numbytes = recvfrom(sockfd,buf,MAXDATASIZE-1,0,
		    rp->ai_addr,&(rp->ai_addrlen)))==-1){
		perror("recvfrom"); 
		continue;
	    }
	    /*display received data*/
	    buf[numbytes] = '\0';
	    printf("client: received form server:\n%s\n",buf);
	}
	freeaddrinfo(servinfo);
	close(sockfd);
	return 0;
}

