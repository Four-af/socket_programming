// PLAYFAIR CIPHER
// Code by Bipin Timalsina
#include <iostream>
#include <string>
using namespace std;

class Playfair
{

public:
    char keyMatrix[5][5];
    string getKey()
    {
        string k;
        cout << "Enter the key:\n";
        cin >> k;
        return k;
    }
    string getMessage()
    {
        string m;
        cout << "Enter the message:\n";
        cin >> m;
        return m;
    }
    // function for encryption
    void encrypt(string msg, string key)
    {
        makeKeyMatrix(key);
        cout << "----------Encryption Process------------" << endl;
        string bg = getBigrams(msg);
        int n = bg.length();
        char ct[n]; // to store cipher text
        int x = 0;
        while (x < n)
        {
            int a_row = 0, a_col = 0, b_row = 0, b_col = 0;
            char ca = ' ', cb = ' ';
            getPosition(bg[x], bg[x + 1], a_row, a_col, b_row, b_col);
            // cout<<a_row<<","<<a_col<<","<<b_row<<","<<b_col;
            if (a_row == b_row)
            {
                ca = keyMatrix[a_row][mod((a_col + 1), 5)];
                cb = keyMatrix[b_row][mod((b_col + 1), 5)];
            }
            else if (a_col == b_col)
            {
                ca = keyMatrix[mod((a_row + 1), 5)][a_col];
                cb = keyMatrix[mod((b_row + 1), 5)][b_col];
            }
            else
            {
                ca = keyMatrix[a_row][b_col];
                cb = keyMatrix[b_row][a_col];
            }

            cout << bg[x] << bg[x + 1] << "--->" << ca << cb << endl;
            ct[x] = ca;
            ct[x + 1] = cb;
            x += 2;
        }
        cout << "\n\n The cipher text is: \n";
        for (int i = 0; i < n; i++)
        {
            cout << ct[i];
        }
    }

    // function for decryption
    void decrypt(string msg, string key)
    {
        makeKeyMatrix(key);
        cout << "----------Decryption Process------------" << endl;
        // string bg = getBigrams(msg);
        int n = msg.length();
        char pt[n]; // to store plain text
        int x = 0;
        while (x < n)
        {
            int a_row = 0, a_col = 0, b_row = 0, b_col = 0;
            char pa = ' ', pb = ' ';
            char c1 = toupper(msg[x]);
            char c2 = toupper(msg[x + 1]);
            getPosition(c1, c2, a_row, a_col, b_row, b_col);
            // cout<<a_row<<","<<a_col<<","<<b_row<<","<<b_col;
            if (a_row == b_row)
            {
                pa = keyMatrix[a_row][mod((a_col - 1), 5)];
                pb = keyMatrix[b_row][mod((b_col - 1), 5)];
            }
            else if (a_col == b_col)
            {
                pa = keyMatrix[mod((a_row - 1), 5)][a_col];
                pb = keyMatrix[mod((b_row - 1), 5)][b_col];
            }
            else
            {
                pa = keyMatrix[a_row][b_col];
                pb = keyMatrix[b_row][a_col];
            }

            cout << msg[x] << msg[x + 1] << "--->" << pa << pb << endl;
            pt[x] = pa;
            pt[x + 1] = pb;
            x += 2;
        }
        cout << "\n\n The plain text is: \n";
        for (int i = 0; i < n; i++)
        {
            cout << pt[i];
        }
    }

private:
    string getBigrams(string msg)
    {
        int len = msg.length();
        char a[len]; // character array of given text
        int n = 0;
        char bigrams[len];
        for (int i = 0; i < len; i++)
        {
            if (msg[i] == ' ')
            { // ignore space
                continue;
            }
            else if (msg[i] == 'j' || msg[i] == 'J')
            {
                a[n] = 'I'; // replace j or J  with I
                n++;
            }
            else
            {
                a[n] = toupper(msg[i]);
                n++;
            }
        }

        // to handle like balloon == ba lx lo on , and more
        int k = 0;
        char filler = 'X';
        bool filled = false;
        for (int i = 0; i < n; i += 2)
        {
            bigrams[k] = a[i];
            k++;
            if (i + 1 != n)
            {
                if (a[i] == a[i + 1] && filled == false)
                {
                    bigrams[k] = filler;
                    k++;
                    bigrams[k] = a[i + 1];
                    k++;
                    filled = true;
                    continue;
                }
                else
                {
                    bigrams[k] = a[i + 1];
                    k++;
                }
            }
        }
        // cout<<k;
        if (k % 2 != 0)
        {
            bigrams[k] = filler;
            bigrams[k + 1] = '\0';
        }
        else
        {
            bigrams[k] = '\0';
        }
        return bigrams;
    }

    // function to generate key matrix
    void makeKeyMatrix(string text)
    {
        int len = text.length();
        char ca[len]; // character array of given string excluding space
        int n = 0;
        for (int i = 0; i < len; i++)
        {
            if (text[i] == ' ')
            {
                continue;
            }
            ca[n] = toupper(text[i]);
            n++;
        }

        // array of alphabets
        char alphabets[26];
        for (int i = 0; i < 26; i++)
        {
            alphabets[i] = i + 65;
        }

        char oneD[26];
        int p = 0;
        oneD[0] = ca[0];
        for (int i = 1; i < n; i++)
        {
            bool duplicate = false;
            for (int j = 0; j < i; j++)
            {
                if (ca[i] == ca[j])
                { // avoid duplicates
                    duplicate = true;
                    break;
                }
            }
            if (duplicate == false)
            {
                oneD[++p] = ca[i];
            }
        }
        if (p < 26)
        {
            for (int i = 0; i < 26; i++)
            {
                bool duplicate = false;
                for (int j = 0; j < p; j++)
                {
                    if (alphabets[i] == oneD[j])
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate == false)
                {
                    oneD[++p] = alphabets[i];
                }
            }
            // to store in keyMatrix
            p = 0;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (oneD[p] == 'J')
                    { // exclude J
                        p++;
                    }
                    keyMatrix[i][j] = oneD[p];
                    p++;
                }
            }
            cout << "The key matrix for Playfair Cipher for given key is: \n";
            // to print keyMatrix

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {

                    cout << keyMatrix[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }

    void getPosition(char a, char b, int &a_row, int &a_column, int &b_row, int &b_column)
    {
        bool match_a = false;
        bool match_b = false;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (keyMatrix[i][j] == a && match_a != true)
                {
                    a_row = i;
                    a_column = j;
                    // cout<<keyMatrix[i][j];
                    match_a = true;
                }
                if (keyMatrix[i][j] == b && match_b != true)
                {
                    b_row = i;
                    b_column = j;
                    // cout<<keyMatrix[i][j];
                    match_b = true;
                }
            }
            if (match_a && match_b)
            {
                break;
            }
        }
    }
    int mod(int a, int b)
    { // to handle modulo operation
        int c = a % b;
        if (c >= 0)
            return c;
        else
            return b + c;
    }
};
int main()
{
    cout << "=======PALYFAIR CIPHER==========" << endl
         << endl;
    int choice;
    char more = 'y';
    Playfair p;
    string m, k;
    while (more == 'y')
    {
        cout << "Enter your choice as following :\n";
        cout << "1. Press 1 for encryption " << endl;
        cout << "2. Press 2 for decryption " << endl;
        cout << "3. Press 3 for exit " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            k = p.getKey();
            m = p.getMessage();
            p.encrypt(m, k);
            break;
        case 2:
            k = p.getKey();
            m = p.getMessage();
            p.decrypt(m, k);
            break;
        case 3:
            exit(1);
        default:
            cout << "Invalid choice!!" << endl;
        }

        cout << "\n\n Do you want to continue?(press y if you want)" << endl;
        cin >> more;
    }
}