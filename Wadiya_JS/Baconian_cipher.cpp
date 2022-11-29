#include <bits/stdc++.h>
using namespace std;
map <char, string>cipher {{'a',"00000"},{'b',"00001"},{'c',"00010"},{'d',"00011"},{'e',"00100"},{'f',"00101"},{'g',"00110"},{'h',"00111"},
        {'i',"01000"},{'j',"01001"},{'k',"01010"},{'l',"01011"},{'m',"01100"},{'n',"01101"},{'o',"01110"},{'p',"01111"},{'q',"10000"},{'r',"10001"},
        {'s',"10010"},{'t',"10011"},{'u',"10100"},{'v',"10101"},{'w',"10110"},{'x',"10111"},{'y',"11000"},{'z',"11001"}};

int main()
{
    string msg;
    int option;
    cout << "1) Encryption \n2) Decryption \n";     
    cin >>option;
    cin.ignore();
    char temp;

    if (option == 1)
    {
        cout << "Enter the string\n";
        getline(cin, msg);
        for (int i = 0; i < msg.length(); i++)
        {
            if (isalpha(msg[i]))
            {
                temp = tolower(msg[i]);
                cout <<cipher.at(temp);
            }
            else if (isspace(msg[i]))
            {
                cout << "";
            }
            else
            {
                cout << msg[i];
            }
        }
        cout << endl;
    }
    if (option == 2)
    {
        string s;
        cout << "Enter the encrypted string\n";
        getline(cin, msg);

        for (int i = 0; i < msg.length(); i = i + 5)
        {
            for (int j = 0; j < 5; j++)
            {
                s = s + msg[i + j];
            }
            for(auto m: cipher){
                if(m.second==s){
                    cout<<m.first;
                }
            }
            s = "";
        }
    }
    cout << endl;
}