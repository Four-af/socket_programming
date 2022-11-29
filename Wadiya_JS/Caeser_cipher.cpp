#include<iostream>
#include<string.h>
using namespace std;
int main() {
   cout<<"Enter the message:";
   string msg; 
   getline(cin,msg);
   int i, j, length,choice,key;
   cout << "Enter key: ";
   cin>>key;
   length = msg.length();
   cout<<"\nEnter your choice\n1. Encryption\n2. Decryption \n";
   cin>>choice;
   if (choice==1){
    string result = "";
    for (int i = 0; i <length; i++) {
        if (isupper(msg[i]))
            result += char(int(msg[i] + key - 65) % 26 + 65);
        else if(msg[i]==' '){
            result+= ' ';
        }
        else
            result += char(int(msg[i] + key - 97) % 26 + 97);
    }
    cout<< result;
   }
   else if (choice == 2) {
    string result = "";
    for (int i = 0; i < msg.length(); i++)
    {
        if (msg[i] >= 'a' && msg[i] <= 'z')
        {
            result.push_back((msg[i] - 'a' - key + 26) % 26 + 'a');
        }
        else if (msg[i] >= 'A' && msg[i] <= 'Z')

        {
            result.push_back((msg[i] - 'A' - key + 26) % 26 + 'A');

        }
        else
        {
            result.push_back(msg[i]);
        }
    }
    cout<< result;
   
   return 0;
}