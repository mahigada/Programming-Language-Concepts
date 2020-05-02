/*
 * parse.cpp
 */
//Mahi Gada
//CS280
#include "parse.h"

namespace Parser {
bool pushed_back = false;
Tok	pushed_token;

static Tok GetNextToken(istream& in, int& line) {
	if( pushed_back ) {
		pushed_back = false;
		return pushed_token;
	}
	return getNextToken(in, line);
}

static void PushBackToken(Tok& t) {
	if( pushed_back ) {
		abort();
	}
	pushed_back = true;
	pushed_token = t;
}
}

static int error_count = 0;

void
ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}

Pt *Prog(istream& in, int& line)
{
	Pt *sl = Sl(in, line);
	if( sl == 0 )
		ParseError(line, "No statements in program");
	if( error_count )
		return 0;
	return sl;
}

// Sl is a Statement followed by a Statement List
Pt *Sl(istream& in, int& line) {
	Pt *s = Stmt(in, line);
	if( s == 0 )
		return 0;

	if( Parser::GetNextToken(in, line) != SC ) {
		ParseError(line, "Missing semicolon");
		delete s;
		return 0;
	}

	return new StmtList(s, Sl(in,line));
}

Pt *Stmt(istream& in, int& line) {
    Tok t = Parser::GetNextToken(in, line);
    if (t == PRINT){
       return PrintStmt(in,line);
    }
    if (t == PRINTLN){
        return PrintlnStmt(in,line);
    }
    if (t == REPEAT){
       return RepeatStmt(in,line);
    }
    if (t==DONE){
    return 0;
    }
    if (t==IDENT){
        Pt *t1 = new Ident(t);
	while ( true ) {
        Tok t = Parser::GetNextToken(in, line);
		if( t != EQ ) {
			Parser::PushBackToken(t);
			return t1;
		}
		Pt *t2 = Sum(in, line);
		if( t2 == 0 ) {
			ParseError(line, "Missing expression after operator");
			return 0;
		}
        t1 = new Assign(t.GetLinenum(), t1, t2);
	}
    }
    else{
    Parser::PushBackToken(t);
    return 0;
    } 
}

Pt *PrintStmt(istream& in, int& line) {
	int l = line;

	Pt *ex = Expr(in, line);
	if( ex == 0 ) {
		ParseError(line, "No expression after print");
		return 0;
	}

	return new Print(l, ex);
}

Pt *PrintlnStmt(istream& in, int& line) {
    int l = line;
	Pt *ex = Expr(in, line);
	if( ex == 0 ) {
		ParseError(line, "No expression after println");
		return 0;
	}
    return new Println(l, ex);
}

Pt *RepeatStmt(istream& in, int& line) {
    Pt *ex = Expr(in, line);
    if(ex == 0){
        ParseError(line, "No Expr following Repeat");
        return 0;
    }
    Tok t = Parser::GetNextToken(in, line);
    if(t.GetToken() != BEGIN){
    ParseError(line, "No Begin following Expression");
    return 0;
    }
    Pt *statement = Stmt(in, line); 
    if(statement ==0){
        ParseError(line, "No Stmt following BEGIN");
        return 0;
    }
    Tok tt = Parser::GetNextToken(in, line);
    if(tt.GetToken() != END){
    ParseError(line, "No End following Statement");
    return 0;
    }
    return new Repeat(line, ex, statement);
}

Pt *Expr(istream& in, int& line) {
Pt *t1 = Sum(in, line);
	if( t1 == 0 ) {
		return 0;
	}

	while ( true ) {
        Tok t = Parser::GetNextToken(in, line);
		if( t != EQ ) {
			Parser::PushBackToken(t);
			return t1;
		}
		Pt *t2 = Sum(in, line);
		if( t2 == 0 ) {
			ParseError(line, "Missing expression after operator");
			return 0;
		}
        t1 = new Assign(t.GetLinenum(), t1, t2);
	}
}

Pt *Sum(istream& in, int& line) {
	Pt *t1 = Prod(in, line);
	if( t1 == 0 ) {
		return 0;
	}
	while ( true ) {
		Tok t = Parser::GetNextToken(in, line);

		if( t != PLUS && t != MINUS ) {
			Parser::PushBackToken(t);
			return t1;
		}
		Pt *t2 = Prod(in, line);
		if( t2 == 0 ) {
			ParseError(line, "Missing expression after operator");
			return 0;
		}
		if( t == PLUS )
			t1 = new PlusExpr(t.GetLinenum(), t1, t2);
		else
			t1 = new MinusExpr(t.GetLinenum(), t1, t2);
	}
}
Pt *Prod(istream& in, int& line) {
Pt *t1 = Primary(in, line);
	if( t1 == 0 ) {
		return 0;
	}
	while ( true ) {
		Tok t = Parser::GetNextToken(in, line);

		if( t != STAR && t != SLASH ) {
			Parser::PushBackToken(t);
			return t1;
		}
		Pt *t2 = Primary(in, line);
		if( t2 == 0 ) {
			ParseError(line, "Missing expression after operator");
			return 0;
		}
		if( t == STAR )
			t1 = new TimesExpr(t.GetLinenum(), t1, t2);
		else
			t1 = new DivideExpr(t.GetLinenum(), t1, t2);
	}
}
Pt *Primary(istream& in, int& line) {
	Tok t = Parser::GetNextToken(in, line);
	if( t == IDENT ) {
		return new Ident(t);
	}
	 if (t == ICONST)
        {
            return new IConst(t);
        }
    if (t == SCONST)
        {
            return new SConst(t);
        }
   if (t == LPAREN)
        {
            Pt *ex = Expr(in, line);
            if(ex == 0){
                ParseError(line, "No Expr following Left Parenthesis");
                return 0; }
            t = Parser::GetNextToken(in, line);
            if(t != RPAREN){
                ParseError(line, "No Right Parenthesis following Expression");
                return 0;
            }
            return ex;
        }
    ParseError(line, "No Primary Expression");
    return 0;
}