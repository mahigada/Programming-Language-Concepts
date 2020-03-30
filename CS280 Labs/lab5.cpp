/*
Write a C++ program that reads from the standard input and counts the number of times each word is seen. 
A word is a number of non-whitespace characters separated by whitespace.
After all input has been processed, print each word that was seen the largest number of times on a line by itself. 
The words should be printed in alphabetical order.
For example, with the input
Hello ... I said Hello are you there?
your program should print out
Hello
since it was the word that appeared most frequently in the input.
With the input
bow wow bow wow
the program should print out two lines:
bow

wow
Because both of those words appeared most frequently in the input.
If there is no input, your program should generate no output.
*/
#include <iostream>
#include <string>
#include <map>
using namespace std;
int main(int argc, char *argv[ ])
{
map<string,int> counters;
string word;
int largest =0;
while( cin>> word ){
    counters[word]++;
    if(counters[word] > largest){
    largest = counters[word];
    }
}
for( auto it = counters.begin(); it != counters.end(); it++ )
    if((it->second) == largest)
    cout<< it->first << endl;
return 0;
    }