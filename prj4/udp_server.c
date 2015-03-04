#include "prj4.h"

int main(int argc, char** argv){
    struct addrinfo hints, *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];

    if(argc != 2){
	fprintf(stderr,"usage: %s port\n", argv[0]);
	exit(EXIT_FAILURE);
    }
//set the struct be zero
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
//wild card addr for server
    s = getaddrinfo(NULL, argv[1],&hints,&result);
    if( s != 0 ){
	fprintf(stderr,"getaddrinfo");
	exit(EXIT_FAILURE);
    }
    
    for( rp = result; rp!=NULL; rp = rp->ai_next){
	sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
	if(sfd == -1)
	    continue;
//show ip address
	char ipstr[INET6_ADDRSTRLEN];
	struct sockaddr_in *hostip= (struct sockaddr_in*)rp->ai_addr;
	void* addr = &(hostip->sin_addr);
	inet_ntop(rp->ai_family,addr,ipstr,sizeof(ipstr));
	printf("host ip: %s\n",ipstr);
//show ip address
	if(bind(sfd, rp->ai_addr,rp->ai_addrlen))
	    break;
	//close(sfd);
    }
    /*TODO: rp is always NULL after above
    if(rp == NULL){
	fprintf(stderr, "Could not bind\n");
	exit(EXIT_FAILURE);
    }
    */
    freeaddrinfo(result);

    for(;;){
	peer_addr_len = sizeof(struct sockaddr_storage);
	nread = recvfrom(sfd,buf,BUF_SIZE,0,
			(struct sockaddr*)&peer_addr,&peer_addr_len);
	if(nread == -1)
	    continue;
	char host[NI_MAXHOST], service[NI_MAXSERV];

	s = getnameinfo( (struct sockaddr*) &peer_addr,
			peer_addr_len,host,NI_MAXHOST,
			service, NI_MAXSERV,NI_NUMERICSERV);
	if(s == 0)
	    printf("Received %ld bytes from %s: %s\n",
			    (long)nread, host, service);
	else
	    fprintf(stderr,"getnameinfo:%s\n",gai_strerror(s));
	if(sendto(sfd,buf,nread,0,(struct sockaddr*)&peer_addr, peer_addr_len)
			!=nread)
	    fprintf(stderr,"Error sending response\n");
    }
    return 0;
}


























