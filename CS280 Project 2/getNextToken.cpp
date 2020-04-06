#include "lex.h"
#include <iostream>
#include <map>
using namespace std;
map<Token, string> myMap = {
    {ERR, "ERR"},
    {DONE, "DONE"},
    {SC, "SC"},
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {STAR, "STAR"},
    {SLASH, "SLASH"},
    {EQ, "EQ"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {PRINT, "PRINT"},
    {PRINTLN, "PRINTLN"},
    {REPEAT, "REPEAT"},
    {BEGIN, "BEGIN"},
    {END, "END"},
    {SCONST, "SCONST"},
    {ICONST, "ICONST"},
    {IDENT, "IDENT"}
};

ostream & operator<< (ostream & out, const Tok & tok)
{
  Token tokenName = tok.GetToken ();
  out << myMap[tokenName];
  if (tokenName == IDENT || tokenName == ICONST || tokenName == SCONST || tokenName == ERR)
    {
      out << "(" << tok.GetLexeme () << ")";
    }
  return out;
}

Tok
getNextToken (istream & in, int &linenum)
{

  enum LexState
  {
    BEGIN,
    IDENT,
    ICONST,
    SCONST,
    ERR,
    DONE,
    COMMENT
  };
  LexState lexstate = BEGIN;
  string lexeme;
  char ch;
  while (in.get (ch))
    {
      switch (lexstate)
	{
	case BEGIN:
	  if (ch == '\n')
	    {
	      linenum++;
	      continue;
	    }
	  if (isspace (ch))
	    {
	      continue;
	    }
	  lexeme = ch;
	  if (isalpha (ch))
	    {
	      lexstate = IDENT;
	    }
	  if (isdigit (ch))
	    {
	      lexstate = ICONST;
	    }
	  if (ch == '"')
	    {
	      lexstate = SCONST;
	    }
	  if (ch == '/')
	    {
	      if (in.peek () == '/')
		{

		  lexstate = COMMENT;
		}
	      else
		{
		  return Tok (SLASH, lexeme, linenum);
		  lexeme = "";
		}
	    }
	  else
	    {
	      if (ch == '+')
		{
		  return Tok (PLUS, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == '-')
		{
		  return Tok (MINUS, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == '*')
		{
		  return Tok (STAR, lexeme, linenum);
		  lexeme = "";
		}

	      if (ch == '=')
		{
		  return Tok (EQ, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == ';')
		{
		  return Tok (SC, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == '(')
		{
		  return Tok (LPAREN, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == ')')
		{
		  return Tok (RPAREN, lexeme, linenum);
		  lexeme = "";
		}

	      if (ch == '.')
		{
		  return Tok (Token::ERR, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == '$')
		{
		  return Tok (Token::ERR, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == '_')
		{
		  return Tok (Token::ERR, lexeme, linenum);
		  lexeme = "";
		}
	      if (ch == '!')
		{
		  return Tok (Token::ERR, lexeme, linenum);
		  lexeme = "";
		}

	    }

	  break;
	case IDENT:
	  if (isdigit (ch) || isalpha (ch))
	    {			//if it is a valid identifier such as x7, keep adding the characters
	      lexeme += ch;
	    }
	  else
	    {
	      in.putback (ch);
	      //if it is not a digit or alphabetical character, it must be a keyword
	      if (lexeme == "print")
		{
		  return Tok (PRINT, lexeme, linenum);
		  lexeme = "";
		}
	      if (lexeme == "println")
		{
		  return Tok (PRINTLN, lexeme, linenum);
		  lexeme = "";
		}
	      if (lexeme == "repeat")
		{
		  return Tok (REPEAT, lexeme, linenum);
		  lexeme = "";
		}
	      if (lexeme == "begin")
		{
		  return Tok (Token::BEGIN, lexeme, linenum);
		  lexeme = "";
		}
	      if (lexeme == "end")
		{
		  return Tok (Token::END, lexeme, linenum);
		  lexeme = "";
		}
	      return Tok (Token::IDENT, lexeme, linenum);
	    }

	  break;
	case ICONST:
	  if (isdigit (ch))
	    {
	      lexeme += ch;
	    }

	  else
	    {
	      in.putback (ch);
	      return Tok (Token::ICONST, lexeme, linenum);
	    }
	  break;
	case SCONST:
	  if (isalpha (ch) || isdigit (ch))
	    {
	      lexeme += ch;
	    }
	  else if (ch == '"')
	    {
	      return Tok (Token::SCONST, lexeme, linenum);
	    }

	  else if (ch == '\\')
	    {
	      lexeme += '\\';
	      if (ispunct (in.peek ()) || isdigit (in.peek ())|| isalpha (in.peek ()))
		{
		  if (in.peek () == 'n')
		    {
		      lexeme += 'n';
		    }
		  else
		    {
		      in.get (ch);
		      lexeme += ch;
		    }
		}
	    }
	  else if (ch == '\n')
	    {
	      lexeme += '\n';
	      return Tok (Token::ERR, lexeme, linenum);
	    }
        
	  else
	    {
	      lexeme += ch;
	    }
	  break;
	case COMMENT:
	  if (ch == '\n')
	    {
	      linenum++;
	      lexstate = BEGIN;
	    }
	  break;
	case ERR:
	  break;
	case DONE:
	  break;
	}
    }
  if (in.eof ())
    {
      return Tok (Token::DONE, lexeme, linenum);
    }
  return Tok ();
}