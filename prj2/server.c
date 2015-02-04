





int main(int argc, char** argv){
/**SERVER is exec'd by the child who has setup ipc in advance*/

/**setup signal handling*/
    server_sa.sa_handler = server_handler;
    server_sa.sa_flags = 0;
    sigset_t zeromask;
    sigemptyset(&server_sa.sa_mask);
    sigemptyset(&zeromask);
    sigaddset(&server_sa.sa_mask,SIGUSR1);
    if( -1 == sigaction(SIGUSR1,&server_sa,NULL) ){
	perror("SERVER:sigaction");
	return 1;
    }

/**read the message from ipc*/



/**process the message to handle file option*/



/**write the result back to the ipc*/



/**signal client and goto sleep*/


}
