#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include "lex.h"
using namespace std;
int main (int argc, char *argv[])
{
  int fileNameCount = 0;
  bool isV = false;
  bool isSconsts = false;
  bool isIds = false;
  bool isIconsts = false;
  ifstream infile;
  istream *in = &cin;


  for (int i = 1; i < argc; i++)
    {
      string command = argv[i];
      //change the boolean if a command has be seen
      if (command == "-v")
	{
	  isV = true;
	}
      else if (command == "-iconsts")
	{
	  isIconsts = true;

	}
      else if (command == "-sconsts")
	{
	  isSconsts = true;

	}
      else if (command == "-ids")
	{
	  isIds = true;
	}
      else
	{
	  if (command.substr (0, 1) == "-")
	    {
	      cerr << "UNRECOGNIZED FLAG " << command << endl;
	      return -1;
	    }
	  fileNameCount++;
	  infile.open (argv[i]);
	  if (!infile.is_open ())
	    {
	      cerr << "CANNOT OPEN " << command << endl;
	      return -1;
	    }
	  else
	    {
	      in = &infile;
	    }
	}
    }
  if (fileNameCount > 1)
    {
      cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
      return -1;
    }
  int linenum = 1;
  int tokenCount = 0;
  Tok t;
  list < string > Indentifiers;
  list < string > Sconsts;
  list < string > Iconsts;
  while ((t = getNextToken (*in, linenum)) != DONE && t != ERR) // process the Token
    {				
      tokenCount++;
      if (isV)
	{
	  cout << t << endl;
	}
      if (isSconsts)
	{
          if (t == SCONST)
	    {
	      Sconsts.push_back (t.GetLexeme ()); //add all strings to a list
	      Sconsts.unique (); //extract only the unique items in the list
	      Sconsts.sort (); //sort the list
	    }
	}

     
      if (isIconsts)
	{
            if (t == ICONST)
	    {
	      Iconsts.push_back (t.GetLexeme ());	//add all integers to a list
	      Iconsts.unique (); //extract only the unique items in the list
	      Iconsts.sort (); //sort the list
	    }
	}
       if (isIds)
	{
	  if (t == IDENT)
	    {
	      Indentifiers.push_back (t.GetLexeme ());	//add all indentifiers to a list
	      Indentifiers.unique (); //extract only the unique items in the list
	      Indentifiers.sort (); //sort the list
	    }
	}
    }
     if(t==ERR){
         cout<<"Error on line "<<linenum <<" ("<<t.GetLexeme ()<<")"<<endl;
         return 1;
      }
     cout << "Lines: " << linenum-1<< endl;
  switch (linenum)
    {
    case 1:
      break;
    default:
      cout << "Tokens: " << tokenCount << endl;
    }
     if (isSconsts && Sconsts.size()>0){
        cout<<"STRINGS: ";
      for (list < string >::iterator s = Sconsts.begin ();
	   s != Sconsts.end (); s++)
	{
	  cout << *s;
	  if (*s != Sconsts.back ()) //if it's not the last item in the list add a comma and space
	    {
	      cout << ", ";
	    }
	  else
	    {
	      cout << endl; //if it's the last item in the list add an endline
	    }
	}
    }
    if (isIconsts && Iconsts.size()>0){
        cout<<"INTEGERS: "<<endl;
         for (list < string >::iterator s = Iconsts.begin ();
	   s != Iconsts.end (); s++)
	{
	  cout << *s;
	  if (*s != Iconsts.back ()) //if it's not the last item in the list add a comma and space
	    {
	      cout << ", ";
	    }
	  else
	    {
	      cout << endl; //if it's the last item in the list add an endline
	    }
	}
    }
  if (isIds && Indentifiers.size()>0)
    {
      cout << "IDENTIFIERS: ";
      for (list < string >::iterator s = Indentifiers.begin ();
	   s != Indentifiers.end (); s++)
	{
	  cout << *s;
	  if (*s != Indentifiers.back ()) //if it's not the last item in the list add a comma and space
	    {
	      cout << ", ";
	    }
	  else
	    {
	      cout << endl; //if it's the last item in the list add an endline
	    }
	}
    }
 
  return 0;
}