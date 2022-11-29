#include<bits/stdc++.h>
using namespace std;
map<int,int> cipher;

void setmatrixrix(string key)
{			
	for(int i=0; i < key.length(); i++)
	{
		cipher[key[i]] = i;
	}
}

string encryptMessage(string msg, string key)
{
	string cipher = "";

	int col = key.length();
	int row = msg.length()/col;
	int i=0;
	if (msg.length() % col)
		row += 1;

	vector<vector<char>> matrix(row,vector<char>(col,' '));
	for (auto &k : msg)
    {
        matrix[i / col][i % col] = k;
        i++;
    }

    string res = "";
    for (int j = 0; j < matrix[0].size(); j++)
    {
        for (int i = 0; i < matrix.size(); i++)
            res += matrix[i][j];
    }
    cipher = res;
	return cipher;
}

string decryptMessage(string msg,string key)
{
    int row = key.length();
    int col = msg.length()/row;
    if(msg.length()%row){
        col++;
    }
    vector<vector<char>>matrix(row,vector<char>(col,'#'));
     int i = 0;
    for (auto &k : msg)
    {
        matrix[i / col][i % col] = k;
        i++;
    }

    string cipher = "";
    for (int j = 0; j < matrix[0].size(); j++)
    {
        for (int i = 0; i < matrix.size(); i++)
            cipher += matrix[i][j];
    }
    return cipher;
}


int main()
{
    cout<<"1) Encryption\n2) Decryption\n";
	int choice;
    cin>>choice;
    cin.ignore();
    if(choice==1){
    string msg;
    string key;
    getline(cin, msg);
    getline(cin, key);
	setmatrixrix(key);
	string cipher = encryptMessage(msg,key);
	cout << "cipher Message: " << cipher << endl;
    }
    else if(choice ==2){
    string msg;
    string key;
    getline(cin, msg);
    getline(cin, key);
	setmatrixrix(key);
	cout << "Decrypted Message: " << decryptMessage(msg,key)<< endl;
    }
	return 0;
}
