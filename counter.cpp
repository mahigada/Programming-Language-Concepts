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
