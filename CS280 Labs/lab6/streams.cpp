#include <iostream>
using namespace std;

#include "lex.h"

int
main()
{
	Tok toks[] = {
		Tok(PRINT,"PRINT",3),
		Tok(PRINTLN,"PRINTLN",3),
		Tok(REPEAT,"REPEAT",3),
		Tok(BEGIN,"BEGIN",3),
		Tok(END,"END",3),
		Tok(IDENT,"foo",3),
		Tok(ICONST,"347",3),
		Tok(SCONST,"hello world",3),
		Tok(PLUS,"+",3),
		Tok(MINUS,"-",3),
		Tok(STAR,"*",3),
		Tok(SLASH,"/",3),
		Tok(EQ,"=",3),
		Tok(LPAREN,"(",3),
		Tok(RPAREN,")",3),
		Tok(SC,";",3),
		Tok(DONE,"DONE",3),
	};
    
    for( int i = 0; toks[i] != DONE; i++ )
        cout << toks[i] << endl;
    
    return 0;
}
