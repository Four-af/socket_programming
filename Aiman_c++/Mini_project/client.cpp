// Client side
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    //  two things req: ip address and port number respectively
    if (argc != 3)
    {
        cerr << "Usage: ip_address port" << endl;
        exit(0);
    }

    // grab the IP address and port number
    char *serverIp = argv[1];
    int port = atoi(argv[2]);

    // setup a socket and connection tools
    struct hostent *host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    // try to connect...
    int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (status < 0)
    {
        cout << "Error connecting to socket!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Connected to the server!" << endl;

    // keeping track of the session time and amount of data sent
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    // creating a message buffer
    char msg[1500];
    string data;

    cout << "Enter data to be sent." << endl;
    cout << ">>>";
    // taking input from client
    getline(cin, data);
    memset(&msg, 0, sizeof(msg)); // clear the buffer

    // sending data to the server
    strcpy(msg, data.c_str());
    bytesWritten += send(clientSd, (char *)&msg, strlen(msg), 0);

    cout << "Awaiting server response..." << endl;
    memset(&msg, 0, sizeof(msg)); // clear the buffer

    // receiving server's message
    bytesRead += recv(clientSd, (char *)&msg, sizeof(msg), 0);
    cout << "\nServer: " << msg << endl;

    // closing the socket descriptors
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "------Session terminated------" << endl;
    cout << "------Session details------" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
         << " secs" << endl;
    cout << "<Connection closed>" << endl;
    return 0;
}