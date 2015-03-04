#include "prj4.h"


int main(int argc, char** argv){
    struct addrinfo hints, *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];

    if(argc<3){
	fprintf(stderr,"Usage: %s host port mesg...\n",argv[0]);
	exit(EXIT_FAILURE);
    }
/*get address*/
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    
    s=getaddrinfo(argv[1],argv[2],&hints,&result);
    if(s!=0){
	fprintf(stderr,"getaddrinfo\n");
	exit(EXIT_FAILURE);
    }

/*open socket*/
    for(rp = result; rp!=NULL; rp=rp->ai_next){
	sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
	if(sfd == -1)
	    continue;
	if(connect(sfd,rp->ai_addr,rp->ai_addrlen)!=-1);
	    break;
	close(sfd);
    }
    if(rp==NULL){
	fprintf(stderr,"Couldnot connect\n");
	exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
/*connect*/
    for(j=3;j<argc;j++){
	len = strlen(argv[j])+1; 
	
	if(len+1 > BUF_SIZE){
	    fprintf(stderr,"No enough buffer\n");
	    continue;
	}
	if(write(sfd,argv[j],len)!= len){
	    fprintf(stderr,"partial/fialed writing\n");
	    exit(EXIT_FAILURE);
	}

	nread = read(sfd,buf,BUF_SIZE);
	if(nread == -1){
	    perror("read");
	    exit(EXIT_FAILURE);
	}
	printf("Recieved %ld bytes: %s\n",(long)nread,buf);
    }
    return 0;
}

























