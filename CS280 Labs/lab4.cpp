/**
Write a C++ program that is given a file name as a command line argument.
Open the file and read it. At the end of the file, print out:
LINES: lc
WORDS: wc
CHARS: cc
DIGITS: dc
Where lc is the number of lines, wc is the number of words, cc is the number of characters, and 
dc is the number of digit characters, 0-9.
If no file name is provided, the program should use the standard input instead of a file.
If the file cannot be opened, print "CANNOT OPEN " followed by a space and the filename, and stop.
The program should ignore any extra command line arguments that are provided after the file name.
**/
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[ ])
{
   istream*in = &cin;
   ifstream infile;
   string line;
   string word;
   int wc =0;
   int cc =0;
   int lc =0;
   int dc =0;
    if(argc==2){
    infile.open(argv[1]);
    if(infile.is_open() )
        in=&infile;
    else { 
        cerr << "CANNOT OPEN " << argv[1] << endl ;
        return -1;
    }
}
    
    
    
    while (getline(*in,line)){
        lc++;
        istringstream ss(line);
        
        for (int i = 0; i < line.length(); i++){
          cc++;
            if (isdigit(line[i]) == true){
             dc++;
            }
        }  
        
    while(ss >> word)
    {
        wc++; 
    }     
    
}
    cc+=lc;
    infile.close();
        cout << "LINES: " << lc << "\nWORDS: " << wc << "\nCHARS: " << cc << "\nDIGITS: " << dc << endl;
        return 0;
}