/**
Write a C++ program that reads in lines of text from the standard input.
Keep a count of the number of lines that you read.
Keep track of the length of the longest line.
Keep count of the number of integers in the input. Remember to check for errors before counting something as an integer. For example, 17 is an integer but 17.4 is not.
When there is no more input, print out three lines of output, as follows:
NUMBER OF LINES: n1
LENGTH OF LONGEST LINE: n2
NUMBER OF INTEGERS: n3
... where n1, n2, n3 are the counts your program kept when processing input.
**/

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


