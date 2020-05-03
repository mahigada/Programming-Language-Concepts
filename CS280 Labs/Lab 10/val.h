#ifndef VALUE_H
#define VALUE_H
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

enum ValType { VINT, VSTR, VERR };

class Value {
    ValType	T;
	int		I;
    string	S;
    
public:
    Value() : T(VERR), I(0) {}
    Value(int vi) : T(VINT), I(vi) {}
    Value(string vs) : T(VSTR), I(0), S(vs) {}
    
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
    bool IsInt() const { return T == VINT; }
    bool IsStr() const { return T == VSTR; }
    
    int GetInt() const { if( IsInt() ) return I; throw "RUNTIME ERROR: Value not an integer"; }
    string GetStr() const { if( IsStr() ) return S; throw "RUNTIME ERROR: Value not a string"; }
        
    // add op to this
    Value operator+(const Value& op) const{
        if(IsInt() && op.IsInt() ){
      int add = GetInt() + op.GetInt();
          return Value(add);
        }
        else if(IsStr() && op.IsStr()) {
            string add = GetStr() + op.GetStr();
          
          return Value(add);
        }
        
        else{
       return Value();
            
        }
        
    }
    // subtract op from this
    Value operator-(const Value& op) const{
          if(IsInt() && op.IsInt() ){
              int sub = GetInt() - op.GetInt();
              return Value(sub);
        }
         else if(op.IsStr() && IsStr() ) {
          return Value(GetStr());
        }
        
        else{
          return Value();
            
        }    
    }
    // multiply this by op
    Value operator*(const Value& op) const;
    // divide this by op
    Value operator/(const Value& op) const;
    
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) {
        out << op.I;
        }
        else if( op.IsStr() ) {
        out << op.S;
        
        }
        else{
        out << "ERROR";
        
        }
        return out;
    }
};

#endif