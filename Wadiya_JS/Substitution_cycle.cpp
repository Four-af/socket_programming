#include<bits/stdc++.h>
using namespace std;
void encrypt(string s, int key, vector<char> &E)
{
    int n = s.length();
    if (key > 26)
    {
        key%=26;
    }
    for (int i = 0; i < n; i++)
    {
        int a = (int)s[i];
        if (a < 65 || a > 122 || (a >= 91 && a <= 96))
        {
            E.push_back(s[i]);
            continue;
        }
        int b = a + key;
        if (b > 90 && (a >= 65 && a <= 90))
        {
            b -= 26;
        }
        else if (b > 122 && (a >= 97 && a <= 122))
        {
            b -= 26;
        }
        else if ((a < 65 && a > 90) || (a < 97 && a > 122) || a == 32)
        {
            E.push_back(s[i]);
            continue;
        }
        E.push_back((char)b);
    }
    cout << "Encrypted string: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cout << E[i];
    }
    cout << endl;
}

void decrypt(vector<char> &E, int key)
{
    vector<char> decrypted;
    int n = E.size();
    int k;
    cout << "Encrypted string: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cout << E[i];
    }
    cout << endl;
    cout << "Enter the key: ";
    cin >> k;
    if (k != key)
    {
        cout << "Wrong key!" << endl;
        return;
    }
    if (key > 26)
    {
        key = key % 26;
    }
    for (int i = 0; i < n; i++)
    {
        int a = (int)E[i];
        if (a < 65 || a > 122 || (a >= 91 && a <= 96))
        {
            decrypted.push_back(E[i]);
            continue;
        }
        int b = a - key;
        if ((b < 65 && E[i] != ' ') || (b > 90 && b < 97))
        {
            b += 26;
        }
        else if ((a < 65 && a > 90) || (a < 97 && a > 122) || a == 32)
        {
            decrypted.push_back(E[i]);
            continue;
        }
        decrypted.push_back((char)b);
    }
    cout << "\nDecrypted string: ";
    for (int i = 0; i < n; i++)
    {
        cout << decrypted[i];
    }
    cout << endl;
}

int main()
{
    string str; int key; int option;
    int flag = 0;
    vector<char> E,V;
    while (1)
    {
        cout << "\n1.Encrypt\n2.Decrypt\n3.Exit\n";
        cout << "Enter option: "<<endl;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter string: ";
            cin>>str;
            cout << "Enter key: ";
            cin >> key;
            encrypt(str, key, E);
            V = E;
            E.clear();
            flag = 1;
            break;
        case 2:
            if (flag == 0)
            {
                cout << "Nothing to decrypt"<<endl;
            }
            else
            {
                decrypt(V, key);
            }
            break;
        default:
            cout<<" Wrong option chosen!"<<endl;
            return 0;
        }
    }
    return 0;
}