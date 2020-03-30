#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
int main (int argc, char *argv[])
{
  istream *in = &cin;
  ifstream infile;
  string line;
  string word;
  int filenameCount = 0;
  string lineCount;
  int LL = 40;
  int IN = 8;

  for (int i = 1; i < argc; i++)
    {
      string command (argv[i]);
      string arg = command.substr (0, 3);
      string digitLL = command.substr (4);
      string digitIN = command.substr (4);
      if (arg == "-LL")
	{
	  if (command.find ("=") == -1)
	    {
	      cout << "MISSING = SIGN " << argv[i] << endl;
	      return -1;
	    }
	  for (int j = 0; j < digitLL.length (); j++)
	    {
	      if (isdigit (digitLL[j]) == false)
		{
		  cout << "VALUE NOT INTEGER > 0 " << argv[i] << endl;
		  return -1;
		}

	    }
	  if (command.substr (0, 4) == "-LL=")
	    {
	      LL = stoi (digitLL);

	    }

	}


      else if (arg == "-IN")
	{
	  if (command.find ("=") == -1)
	    {
	      cout << "MISSING = SIGN " << argv[i] << endl;
	      return -1;
	    }
	  for (int k = 0; k < digitIN.length (); k++)
	    {
	      if (isdigit (digitIN[k]) == false)
		{
		  cout << "VALUE NOT INTEGER > 0 " << argv[i] << endl;
		  return -1;
		}
	    }
	  if (command.substr (0, 4) == "-IN=")
	    {
	      IN = stoi (digitIN);

	    }
	}
      else
	{
	  if (command.substr (0, 1) == "-")
	    {
	      cerr << "UNRECOGNIZED FLAG " << argv[i] << endl;
	      return -1;
	    }
	  filenameCount++;
	  infile.open (argv[i]);
	  if (!infile.is_open ())
	    {
	      cerr << "UNABLE TO OPEN FILE " << argv[i] << endl;
	      return -1;
	    }
	  else
	    {
	      in = &infile;
	    }
	}
    }
  if (filenameCount > 1)
    {
      cerr << "TOO MANY FILENAMES" << endl;
      return -1;
    }
  string str;
  string indent = "";
  bool multipleEmptyLine = true;
  bool inPara = true;
  int outLen = 0;
  while (getline (*in, str))
    {
        
      bool blank = true;
      for (int l = 0; l < str.length (); l++)
	{
	  if (!isspace (str[l]))
	    {
	      blank = false;
	      multipleEmptyLine = false;
	    }
	}
      if (inPara)
	{
	  if ((str.empty () || blank) && !multipleEmptyLine)
	    {
	      inPara = false;
	      cout << endl;
	      cout << endl;
	    }
	  else
	    {
	      string word;
	      istringstream ss (str);
	      while (ss >> word)
		{
		  if (outLen == 0)
		    {
		      for (int k = 0; k < IN; k++)
			{
			  cout << " ";
			}
		      outLen += IN;
		      cout << word;
		      outLen += word.length ();
		    }
		  else if (outLen + word.length () + 1 <= LL)
		    {
		      cout << " " << word;
		      outLen += word.length () + 1;
		    }
		  else
		    {
		      cout << endl << word;
		      outLen = word.length ();
		    }
		}
	    }
	}
      else
	{
	  if (!((str.empty () || blank) && !multipleEmptyLine))
	    {
	      inPara = true;
	      outLen = 0;
	    }
	  string word;
	  istringstream ss (str);
	  while (ss >> word)
	    {
	      if (outLen == 0)
		{
		  for (int k = 0; k < IN; k++)
		    {
		      cout << " ";
		    }
		  outLen += IN;
		  cout << word;
		  outLen += word.length ();
		}
	      else if (outLen + word.length () + 1 <= LL)
		{
		  cout << " " << word;
		  outLen += word.length () + 1;
		}
	      else
		{
		  cout << endl << word;
		  outLen = word.length ();
		}
	    }
	}
    }
  if (multipleEmptyLine)
    {
      cout << endl;
    }
  else
    {
      cout << endl;
    }

  infile.close ();
  return 0;
}
