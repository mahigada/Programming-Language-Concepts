/*
 * pt.h
 */
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
#include "val.h"
//static map<string,Value> symbols;

class Value;
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
    //Pt *GetLeft() const { return left; }
	//Pt *GetRight() const { return right; }
    
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
    virtual Value Eval(map<string,Value>& symbols)=0;
    void CheckAssignments(map<string,bool>& var) {
		if( left ) left->CheckAssignments(var);
		if( right ) right->CheckAssignments(var);
        this->CheckAssign(var);
    }
        
	virtual void CheckAssign(map<string,bool>& var) {
		return;
	}
};

class StmtList : public Pt {
public:
	StmtList(Pt *l, Pt *r) : Pt(0, l, r) {}
    Value Eval(map<string,Value>& symbols) {
        left->Eval(symbols);
        if( right )
            right->Eval(symbols);
        return Value();
    }
};

class Print : public Pt {
public:
	Print(int line, Pt *e) : Pt(line, e) {}
     Value Eval(map<string,Value>& symbols) {
        Value val1 = left->Eval(symbols);
        cout <<val1;
        return Value(val1);
    }
};

class Println : public Pt {
public:
	Println(int line, Pt *e) : Pt(line, e){}
     Value Eval(map<string,Value>& symbols) {
        Value val1 = left->Eval(symbols);
        cout <<val1<<endl;
        return Value(val1);
    }
};

class Repeat : public Pt {
public:
	Repeat(int line, Pt *e, Pt *stmt) : Pt(line, e, stmt) {}
    Value Eval(map<string,Value>& symbols) {
        Value val1 = left->Eval(symbols);
        if (val1.GetInt()!=0){
            int getVal1 =val1.GetInt();
            Value val2 = right->Eval(symbols);
            while(getVal1>1){
                val2 = right->Eval(symbols);
                getVal1--;
            }
        }
        else{
            throw ("control expression not an integer");
        }
        return Value();
    } 
};

class Assign : public Pt {
    string valKey;
 public:
    Assign(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
    string getId() const { return valKey; }
    bool isEq() const { return true; }
    virtual void CheckAssign(map<string,bool>& var) {
		right->CheckAssign(var);
		var[ this->valKey ] = true;
	}
    Value Eval(map<string,Value>& symbols) {
        
        Value val1 = right->Eval(symbols);
        symbols[left->getId()]=val1;
        return Value(val1);
    } 
    
};

class PlusExpr : public Pt {
public:
    PlusExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
     Value Eval(map<string,Value>& symbols) {
        auto val1 = left->Eval(symbols);
        auto val2 = right->Eval(symbols);
        return val1+val2;
    }
    
    bool isPlus() const { return true; }
};

class MinusExpr : public Pt {
    public:
    MinusExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
     Value Eval(map<string,Value>& symbols) {
        auto val1 = left->Eval(symbols);
        auto val2 = right->Eval(symbols);
        return val1-val2;
    }

};
class TimesExpr: public Pt {
    public:
    TimesExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
    Value Eval(map<string,Value>& symbols) {
        auto val1 = left->Eval(symbols);
        auto val2 = right->Eval(symbols);
        return val1*val2;
    }
};

class DivideExpr : public Pt {
public:
    DivideExpr(int line, Pt *l, Pt *r) : 
    Pt(line,l,r) {}
    Value Eval(map<string,Value>& symbols) {
        auto val1 = left->Eval(symbols);
        auto val2 = right->Eval(symbols);
        return val1/val2;
    }
};

class IConst : public Pt {
	int val;

public:
	IConst(Tok& t) : Pt(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
    Value Eval(map<string,Value>& symbols) {
        return Value(val);
    }
};

class SConst : public Pt {
	string val;

public:
	SConst(Tok& t) : Pt(t.GetLinenum()) {
		val = t.GetLexeme();
	}
    Value Eval(map<string,Value>& symbols) {
        return Value(val);
    }
};

class Ident : public Pt {
	string val2;
public:
    string getId() const { return val2; }
    Ident(Tok& t) : Pt(t.GetLinenum()), val2(t.GetLexeme()) {}
    Value Eval(map<string,Value>& symbols) {
        
        if(symbols.find(val2)!=symbols.end()){
            
            return symbols[val2];   
        }
        else{    
          throw "at " + to_string(GetLineNumber() + 1) + ": Variable used but not assigned";
        }
         return Value();
    }
    virtual void CheckAssign(map<string,bool>& var) {
        if( var.find(getId()) == var.end() )
            cout << "UNDECLARED VARIABLE " << getId() << endl;
    }
	bool isIdent() const { return true; }
};
#endif /* PT_H_ */