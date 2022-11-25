/************************************************************
Program: Play Fair cypher encipher-decipher
Author: Mujtaba Asif
e-Mail: mjtbasif@gmail.com
Date: 11/18/2017
************************************************************/
// *~~~~~~~~ header declaration ~~~~~~~~~~* //
#include<bits/stdc++.h>
using namespace std;

// *~~~~~~~~ variable declaration ~~~~~~~~~~* //
char grid[5][5]; // 5x5  matrix to encipher or decipher
char keyword[26]; // cypher key
char msg[100]; // message
int mark[130],len,r,c; // necessary variables

// *~~~~~~~~~ Function declaration ~~~~~~~~~~~* //
void createGrid();
void showGrid();
void encipher();
void decipher();
void initialize();
void menu()
{
    system("CLS");
    int n;
    string op[]={"1. Encipher","2. Decipher","3. Exit"};
    cout<<op[0]<<endl<<op[1]<<endl<<op[2]<<endl<<"Enter choice: ";
    cin>>n;
    if(n==1) encipher();
    else if(n==2) decipher();
    else exit(1);
}
void initialize()
{
    memset(mark,0,sizeof(mark));
    system("CLS");
}
int main()
{
    menu();
    return 0;
}
void decipher()
{
    initialize();
    createGrid();
    cout<<"Cypher text: ";
    char cypText[150]; // cypher text
    cin>>cypText;
    getchar(); // flush buffer
    int l=strlen(cypText); //take length

    /*
    for(int i=0;i<l;i+=2)
        cout<<cypText[i]<<cypText[i+1]<<" ";
    cout<<endl;
    */

    cout<<"Decipher text: ";
    //decipher starts
    int P,Q,R,S,f1,f2;
    char x,y;
    for(int i=0;i<l;i+=2)
    {
        x=cypText[i];
        y=cypText[i+1];
        f1=f2=0;
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(x==grid[j][k])
                {
                    P=j;
                    Q=k;
                    f1=1;
                }
                if(y==grid[j][k])
                {
                    R=j;
                    S=k;
                    f2=1;
                }
                if(f1 && f2) break;
            }
             if(f1 && f2) break;
        }
        if(P==R) //same row
        {
            if(Q==0) cout<<grid[P][4];
            else cout<<grid[P][Q-1];
            if(S==0) cout<<grid[R][4];
            else cout<<grid[R][S-1];
        }
        else if(Q==S ) // same column
        {
            if(P==0) cout<<grid[4][Q];
            else cout<<grid[P-1][Q];
            if(R==0) cout<<grid[4][S];
            else cout<<grid[R-1][S];
        }
        else //opposite corner
        {
            cout<<grid[P][S]<<grid[R][Q];
        }
    }
    cout<<endl<<endl;
    system("PAUSE");
    menu();
}
void encipher()
{
    initialize();
    createGrid();
    cout<<"Message to cypher: ";
    gets(msg);
    int l=strlen(msg); // msg length
    char reqText[150]; //generate required text to encipher
    int in=0,j=0;
    for(int i=0;i<l;i++)
    {
        j=i+1;
        if(msg[i]==' ') //ignore all space from string
        {
            i++;
            j++;
        }
        if(msg[j]==' ') j++; //ignore space
        if(toupper(msg[i])=='J') msg[i]='i'; // ignore J
        if(toupper(msg[i])==toupper(msg[j])) // if duplicate add 'X' after the first letter
        {
            reqText[in]=toupper(msg[i]);
            reqText[in+1]='X';
            in++;
        }
        else
        {
            reqText[in]=toupper(msg[i]);
        }
        in++;
    }
    if(in%2!=0) reqText[in]='X'; // if one character left, add 'X' after it

    /*
    //show generated text in pair
    for(int i=0;i<in;i+=2)
        cout<<reqText[i]<<reqText[i+1]<<" ";
    cout<<endl;
    */

    cout<<"Cypher text: ";
    //encipher starts
    int P,Q,R,S,f1,f2;
    char x,y;
    for(int i=0;i<in;i+=2)
    {
        x=reqText[i];
        y=reqText[i+1];
        f1=f2=0;
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(x==grid[j][k])
                {
                    P=j;
                    Q=k;
                    f1=1;
                }
                if(y==grid[j][k])
                {
                    R=j;
                    S=k;
                    f2=1;
                }
                if(f1 && f2) break;
            }
             if(f1 && f2) break;
        }
        if(P==R) //same row
        {
            if(Q==4) cout<<grid[P][0];
            else cout<<grid[P][Q+1];
            if(S==4) cout<<grid[R][0];
            else cout<<grid[R][S+1];
        }
        else if(Q==S ) // same column
        {
            if(P==4) cout<<grid[0][Q];
            else cout<<grid[P+1][Q];
            if(R==4) cout<<grid[0][S];
            else cout<<grid[R+1][S];
        }
        else //opposite corner
        {
            cout<<grid[P][S]<<grid[R][Q];
        }
    }
    cout<<endl<<endl;
    system("PAUSE");
    menu();
}
void createGrid()
{
    cout<<"Keyword: ";
    cin>>keyword; // key of the cypher
    getchar();
    len=strlen(keyword);  // size of input string O(n) :3
    mark['J']=1; // ignore J
    r=0,c=0; //initialize row and column

    // first populate the keyword
    for(int i=0;i<len;i++)
    {
        if(!mark[toupper(keyword[i])]) // ignore duplicates
        {
            mark[toupper(keyword[i])]=1;
            grid[r][c++]=toupper(keyword[i]);
            if(c%5==0) //increase row column
            {
                c=0;
                r++;
            }
        }
    }

    // complete rest of the matrix from unused characters starting from A
    for(int i='A';i<='Z';i++)
    {
        if(mark[i]==0) // taking values that are not in the matrix already
        {
            grid[r][c++]=i;
            mark[i]=1;
            if(c%5==0)
            {
                if(r==4 && c==5) break; //matrix populated

                // else increase row column
                r++;
                c=0;
            }
        }
    }
}
void showGrid()
{
    cout<<"5x5 Matrix"<<endl;
    //show grid
   for(int i=0;i<5;i++)
   {
       for(int j=0;j<5;j++)
       {
           cout<<grid[i][j]<<" ";
       }
       cout<<endl;
   }
}