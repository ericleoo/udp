#include "udp_client_server.h"
#include <iostream>
using namespace std;
using namespace udp_client_server;
#define HEADER_SIZE 4

int portno;
char header[1];
char *buffer;
int message_length;

/*
void send(udp_server &server){
    server.send(header,HEADER_SIZE);
    server.send(buffer,message_length);
}
*/

void receive(udp_server &server){
    cout << "WAITING\n";
    server.recv(header,HEADER_SIZE);
    char received = *header;
    cout << "Received: " << (int)received << '\n';
}

int main(int argc, char **argv){
    if (argc != 2) portno = 8080;
    else portno = atoi(argv[1]);
    udp_server server("127.0.0.1",8080);
    while(true){
        receive(server);
    }
    return 0;
}
