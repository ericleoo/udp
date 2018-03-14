#include "udp_client_server.h"
#include <iostream>
using namespace std;
using namespace udp_client_server;
#define HEADER_SIZE 4

int portno;
char header[1];
char *buffer;
int message_length;

int main(int argc, char **argv){
    if (argc != 3){
        cout << "USAGE: <ip> <port>\n";
        return 0;
    }
    portno = atoi(argv[2]);
    udp_client client(argv[1],8080);
    for(char i=0;i<20;i++)
        header[0] = i, client.send(header,1);
    return 0;
}
