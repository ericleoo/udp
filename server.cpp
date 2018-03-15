#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * error - wrapper for perror
 */

class udp_server{
private:
    int sockfd; /* socket */
    int portno; /* port to listen on */
    unsigned clientlen; /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp; /* client host info */
    char *hostaddrp; /* dotted decimal host addr string */
    int optval; /* flag value for setsockopt */
    int n; /* message byte size */
public:
    
    void receive(char *buf, size_t bufsize){
        printf("WAITING\n");
        n = recvfrom(sockfd, buf, bufsize, 0, (struct sockaddr *) &clientaddr, &clientlen);
        printf("RECEIVED\n");
        if (n < 0) perror("ERROR in recvfrom");

        hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (hostp == NULL) perror("ERROR on gethostbyaddr");
        hostaddrp = inet_ntoa(clientaddr.sin_addr);
        if (hostaddrp == NULL) perror("ERROR on inet_ntoa\n");
        printf("server received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
        printf("server received %d/%d bytes: %d\n", strlen(buf), n, (int)(buf[0]));
    }

    void send(const char *buf, size_t bufsize){
        sendto(sockfd, buf, bufsize, 0, (struct sockaddr *) &clientaddr, clientlen);
    }
    
    udp_server(int port){
        portno = port;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        if (sockfd < 0){
            perror("ERROR opening socket");
            return;
        }
        
        optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
        
        bzero((char *) &serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons((unsigned short)portno);

        if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) 
            perror("ERROR on binding");
        
        clientlen = sizeof(clientaddr);
    }
};


char header[1];

int main(int argc, char **argv) {
    udp_server server = udp_server(8080);
    while(true){
        server.receive(header,1);
        server.send(header,1);
    }
}
