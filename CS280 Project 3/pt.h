/*
 * pt.h
 */
//Mahi Gada
//CS280
#ifndef PT_H_
#define PT_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::vector;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "parse.h"
#include "lex.h"

class Pt {
public:
	int	linenum;
	Pt	*left;
	Pt	*right;

public:
	Pt(int linenum, Pt *l = 0, Pt *r = 0)
		: linenum(linenum), left(l), right(r) {
        }

	virtual ~Pt() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }
    
    int plusCount() const {
        int counter=0;
        if( left) counter += left->plusCount();
		if( right) counter += right->plusCount();
        if(isPlus()){
            counter++;
        }
		return counter;
	}
     int eqCount() const {
        int counter=0;
        if( left) counter += left->eqCount();
		if( right) counter += right->eqCount();
        
        if(isEq()){
            counter++;
        }
		return counter;
	}

int depthCount() const {
    int Rcounter=0;
    int Lcounter=0;
        if( left) Lcounter += left->depthCount();
		if( right) Rcounter += right->depthCount();
    if (Rcounter>Lcounter){
        return Rcounter +1;
    }
    else{
    return Lcounter +1;
    }
	}
    virtual bool isPlus() const { return false; }
    virtual bool isEq() const { return false; }
	virtual bool isIdent() const { return false; }
	virtual bool isVar() const { return false; }
	virtual string getId() const { return ""; }

};

class StmtList : public Pt {
public:
	StmtList(Pt *l, Pt *r) : Pt(0, l, r) {}
};

class Print : public Pt {
public:
	Print(int line, Pt *e) : Pt(line, e) {}
};

class Println : public Pt {
public:
	Println(int line, Pt *e) : Pt(line, e){}
};

class Repeat : public Pt {
public:
	Repeat(int line, Pt *e, Pt *stmt) : Pt(line, e, stmt) {}

};

class Assign : public Pt {
 public:
    Assign(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
    bool isEq() const { return true; }
};

class PlusExpr : public Pt {
public:
    PlusExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
    bool isPlus() const { return true; }
};

class MinusExpr : public Pt {
    public:
    MinusExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}

};
class TimesExpr: public Pt {
    public:
    TimesExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
};

class DivideExpr : public Pt {
public:
    DivideExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
};

class IConst : public Pt {
	int val;

public:
	IConst(Tok& t) : Pt(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
};

class SConst : public Pt {
	string val;

public:
	SConst(Tok& t) : Pt(t.GetLinenum()) {
		val = t.GetLexeme();
	}
};

class Ident : public Pt {
	string val2;
public:
	Ident(Tok& t) : Pt(t.GetLinenum()) {
		val2 = t.GetLexeme();
	}
	bool isIdent() const { return true; }
};
#endif /* PT_H_ */