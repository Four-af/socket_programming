#include <bits/stdc++.h>
using namespace std;
#define ll long long

/// 5*5 key table
void keyTable(char key[], int ks, char keyT[5][5])
{
    int i, j, k, flag = 0;

    // a 26 character hashmap
    // to store count of the alphabet
    int dicty[26] = {0};
    for (i = 0; i < ks; i++)
    {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }

    dicty['j' - 97] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < ks; k++)
    {
        if (dicty[key[k] - 97] == 2)
        {
            dicty[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++)
    {
        if (dicty[k] == 0)
        {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
}

void search(char keyT[5][5], char a, char b, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++)
    {

        for (j = 0; j < 5; j++)
        {

            if (keyT[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

string dec(int num)
{
    return "";
}

void dkrpt(string s)
{
}

string enkrpt(string s)
{
}

int main()
{

    cout << "\n20BCS008 Aiman Fatima\n\n";
    cout << "\n20BCS008 Aiman Fatima\n\n";
    string s, ans;
    char yn;
    while (1)
    {
        cout << "\n----Menu----\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Dencrypt an already encrypted message\n";
        cout << "3. Exit\n";
        int choice;
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\n\nEnter string : ";
            fflush(stdin);
            getline(cin, s);
            ans = enkrpt(s);
            cout << "\nEncrypted text is : " << ans;
            cout << "\n\nDo you want to decrypt your encrpted string ? (y/n) : ";
            cin >> yn;
            if (yn == 'y')
            {
                dkrpt(ans);
                break;
            }
            else
                break;

        case 2:
            cout << "Enter string to be decrypted : ";
            //				s.clear();
            fflush(stdin);
            getline(cin, s);
            dkrpt(s);
            break;
        case 3:
            cout << "\nThe End\n";
            return 0;
        default:
            "\nWrong choice\n";
            break;
        }
    }

    //
    return 0;
}