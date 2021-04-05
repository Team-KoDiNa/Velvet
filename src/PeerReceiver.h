#ifndef PeerReceiver_h
#define PeerReceiver_h

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <regax.h>
#include <thread>
#include <iostream>

class PeerReceiver {

private:
    std::string ReciverName = "";
    std::string ReceiverPort = "";
    int sockfd = 0, newsockfd = 0, portno = 0;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256] = {0};
    void FileReaderAndReceiver(char*,int);
    int GerFilesize(FILE*);
    void listfiles(int);
    void listCommand(char[]);
    
public:
    PeerReceiver(std::string, std::string);
    void StartReciver();
};


#endif
