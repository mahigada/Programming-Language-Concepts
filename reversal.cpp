/**
For this assignment, we define three types of "reversal"
A "line" reversal reverses the entire line. In a line reversal, "Hello world!" becomes "!dlrow olleH"
A "word" reversal reverses each word. In a word reversal, "Hello world!" becomes "olleH !dlrow"
A "lineword" reversal performs a line reversal and a word reversal. In a lineword reversal, "Hello world!" becomes "world! Hello".
No matter how many spaces between words in the input, the output should have only one space after each word. 
So a line reversal of "Hello                                              world!" becomes "!dlrow olleH"
Write a C++ program that does line, word and lineword reversals. The program is told which type of reversal to perform 
by providing a single command line argument, "line", "word", or "lineword".
If no command line arguments are provided, the program should print "MISSING FLAG" and stop.
If an unrecognized command line argument is provided, the program should print "UNKNOWN FLAG" followed by the 
unrecognized argument, and stop.
If more than one command line argument is provided, the program should print "TOO MANY FLAGS" and stop.
**/
#include <iostream>
#include <algorithm>
using namespace std;
void lineRev(string str) 
{
    reverse(str.begin(), str.end()); 
    cout << str << endl; 
}
void wordRev (string str){
string temp = "";
for (int i=0; i<str.length();i++){
    if(str[i] == ' '){
    reverse(temp.begin(), temp.end());
    cout << temp << str[i] ;
    temp.clear();
    }
   else if (i == str.length()-1){
     temp += str[i];
     reverse(temp.begin(), temp.end());
     cout << temp << endl;
      }
    else{
    temp+=str[i];
    }
}}

void lineWordRev(string str){
string temp = "";
for(int i=str.length()-1;i>=0;i--) {
if(str[i] == ' '){
    reverse(temp.begin(), temp.end());
    cout << temp << str[i] ;
    temp.clear();
}
else if (i == 0){
     temp += str[i];
     reverse(temp.begin(), temp.end());
     cout << temp << endl;
      }
else{
    temp+=str[i];
    }
}
}


int main(int argc, char *argv[ ])
{
string strIn; 
string str(argv[1]); 
if(argc < 2){
cout << "MISSING FLAG"<< endl;
}
if(argc > 2) {
cout << "TOO MANY FLAGS"<< endl ; 
}
else if( argc == 2) 
{
     while(getline(cin, strIn)) 
{
if(str.compare("line") == 0)
lineRev(strIn);
else if(str.compare("word") == 0)
wordRev(strIn);
else if(str.compare("lineword") == 0)
lineWordRev(strIn);
else
{
cout << "UNKNOWN FLAG " << str << endl; 
}}}
return 0; 
}
