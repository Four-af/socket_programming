// Server side
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

// function to check palindrome
bool palindrome(string s)
{
    for (int i = 0; i <= s.size() / 2; i++)
    {
        if (s[i] != s[s.size() - 1 - i])
            return false;
    }
    return true;
}

// main function
int main(int argc, char *argv[])
{
    // for the server, we only need to specify a port number
    if (argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    // grab the port number
    int port = atoi(argv[1]);

    // setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char *)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    // open stream oriented socket with internet address
    // also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    // binding the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr *)&servAddr,
                          sizeof(servAddr));
    if (bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    // listen for up to 5 requests at a time
    listen(serverSd, 5);

    // receive a request from client using accept
    // we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    // accept, create a new socket descriptor to
    // handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if (newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client!" << endl;

    // keeping track of the session time and amount of data sent
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    int bytesRead, bytesWritten = 0;

    // buffer to send and receive messages with
    char msg[1500];
    // variables
    string received_string;
    bool checker;
    string data;

    cout << "Awaiting client response..." << endl;
    memset(&msg, 0, sizeof(msg)); // clear the buffer
    bytesRead += recv(newSd, (char *)&msg, sizeof(msg), 0);
    received_string = msg;
    cout << "\nClient: " << received_string << endl;

    // checking for palindrom
    checker = palindrome(received_string);

    memset(&msg, 0, sizeof(msg)); // clear the buffer
    if (checker)
        data = "Data received is a palindrome\n";
    else
        data = "Data received is not a palindrome\n";

    // send the message to client
    strcpy(msg, data.c_str());
    bytesWritten += send(newSd, (char *)&msg, strlen(msg), 0);

    // closing the socket descriptors
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "\n------Session terminated------" << endl;
    cout << "------Session details------" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
         << " secs" << endl;
    cout << "<Connection closed>" << endl;
    return 0;
}