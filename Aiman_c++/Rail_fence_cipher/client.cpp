// Client side
#include <bits/stdc++.h>
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

string EncryptRail(string text, int key)
{
    char rail[key][(text.length())];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';
    bool dir_down = false;
    int row = 0, col = 0;
    for (int i = 0; i < text.length(); i++)
    {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        rail[row][col++] = text[i];
        dir_down ? row++ : row--;
    }
    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);
    return result;
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

string encrypt(string str, string key)
{
    string cipher_text;

    for (int i = 0; i < str.size(); i++)
    {
        // converting in range 0-25
        char x = (str[i] + key[i]) % 26;

        // convert into alphabets(ASCII)
        x += 'A';

        cipher_text.push_back(x);
    }
    return cipher_text;
}

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
    string data, key;

    cout << "Enter data string" << endl;
    cout << ">>>";
    // taking input string from client
    getline(cin, data);
    cout << "Enter key" << endl;
    cout << ">>>";
    // taking input key from client
    getline(cin, key);
    // toupper(data);
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    // key = toupper(key);
    int keyword = stoi(key);
    //
    // key = generateKey(data, key);

    // calling cipher function
    string ans = EncryptRail(data, keyword);
    memset(&msg, 0, sizeof(msg)); // clear the buffer
    cout << "<< Sending Encrypted Data : " << ans << " >>\n";

    ans = ans + '$' + key;

    // sending data to the server
    strcpy(msg, ans.c_str());
    bytesWritten += send(clientSd, (char *)&msg, strlen(msg), 0);

    cout << "Awaiting server response..." << endl;
    memset(&msg, 0, sizeof(msg)); // clear the buffer

    // receiving server's message
    bytesRead += recv(clientSd, (char *)&msg, sizeof(msg), 0);
    cout << "\nServer: " << msg << endl;

    // closing the socket descriptors
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "\n------Session terminated------" << endl;
    cout << "------Session details------" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
         << " secs" << endl;
    cout << "<Connection closed>" << endl;
    return 0;
}