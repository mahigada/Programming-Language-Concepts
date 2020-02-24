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
