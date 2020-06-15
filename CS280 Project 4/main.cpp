//CS280
//Mahi Gada
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include "lex.h"
#include "parse.h"
#include "pt.h"

using namespace std;
int linenum = 0;
ifstream infile;
istream *in = &cin;

int
main (int argc, char *argv[])
{
    map<string,Value> symbols;

  for (int i = 1; i < argc; i++)
    {
      string command = argv[i];
      //change the boolean if a command has be seen
      if (i == 1)
	{
        
	  infile.open (argv[i]);
	  if (!infile.is_open ())
	    {
	      cerr << "CANNOT OPEN " << command << endl;
	      return -1;
	    }
	  in = &infile;      
	}
      if (i>1){
      cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
      return -1;
      }
    }
    
    Pt *prog = Prog(*in, linenum);
    if (prog == nullptr){
        
        return -1;
    }
    if (prog != 0)
    {
      try {prog->Eval(symbols);
          }
        catch( std::string& e ) {
             
            cout<< "RUNTIME ERROR "  << e << endl;
        } 
        catch(char const*e){
            
            cout<<"RUNTIME ERROR at "<<linenum <<": "<< e <<endl;
        }
        
        
     }
  return 0;
}
