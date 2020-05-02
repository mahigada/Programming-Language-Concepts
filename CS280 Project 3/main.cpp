//Mahi Gada
//CS280
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include "lex.h"
#include "parse.h"

using namespace std;
int linenum = -1;
ifstream infile;
istream *in = &cin;

int
main (int argc, char *argv[])
{

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
        cout<<"PLUS COUNT: " << prog->plusCount()<<endl;
        cout<<"EQ COUNT: " << prog->eqCount()<<endl;
        cout<<"MAX DEPTH: "<< prog->depthCount()<<endl;
     }
  return 0;
}