#include <iostream>
#include <sstream>
using namespace std;
int main()
{
string str;
int numOfLines, numOfInts, longestLength =0;
while(getline(cin, str))
{ 
    numOfLines++;
    if(str.length()>longestLength){
    longestLength = str.length();
    }
    istringstream ss(str);
    string num;
    
    while(ss >> num)
    {
     bool isDig = true;   
        for (int i = 0; i < num.length(); i++){
          if (isdigit(num[i]) == false){
              isDig = false;
}
        } 
        if(isDig == true)
        numOfInts++;
}       
    }
cout<<"NUMBER OF LINES: "<<numOfLines<<endl;
cout<<"LENGTH OF LONGEST LINE: "<<longestLength<<endl;
cout<<"NUMBER OF INTEGERS: "<<numOfInts<<endl;
return 0;
}


