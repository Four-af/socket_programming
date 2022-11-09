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

// function to decrypt
string decrypt(string cipher_text, string key)
{
    string orig_text;

    for (int i = 0; i < cipher_text.size(); i++)
    {
        // converting in range 0-25
        char x = (cipher_text[i] - key[i] + 26) % 26;

        // convert into alphabets(ASCII)
        x += 'A';
        orig_text.push_back(x);
    }
    return orig_text;
}
string generateKey(string str, string key)
{
    int x = str.size();

    for (int i = 0;; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}
string parsing_str(string mssg)
{
    string a = "";
    for (int i = 0; i < mssg.size(); i++)
    {
        if (mssg[i] == '$')
        {
            break;
        }
        else
            a += mssg[i];
    }
    return a;
}

string parsing_key(string mssg)
{
    string a = "";
    int idx;
    for (int i = 0; i < mssg.size(); i++)
    {
        if (mssg[i] == '$')
        {
            idx = i;
            break;
        }
        // else a+=mssg[i];
    }
    a = mssg.substr(idx + 1, mssg.size() - (idx + 1));
    return a;
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

    // differentiating btwn key and string
    string str = parsing_str(received_string);
    string key = parsing_key(received_string);
    cout << "\nEncrypted String : " << str << "\n";

    key = generateKey(str, key);
    cout << "\nKey : " << key << "\n";

    // decrypt
    data = decrypt(str, key);

    memset(&msg, 0, sizeof(msg)); // clear the buffer
    cout << "Decrypted Text : " << data << endl;
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