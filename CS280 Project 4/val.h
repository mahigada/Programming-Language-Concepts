#ifndef VALUE_H
#define VALUE_H

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
    
    int GetInt() const { if( IsInt() ) return I; throw "control expression not an integer"; }
    string GetStr() const { if( IsStr() ) return S; throw "RUNTIME ERROR: Value not a string"; }
    
        
    // add op to this
   Value operator+(const Value& op) const{
       if(IsInt() && op.IsInt() ){
           int add = I + op.GetInt();
           return Value(add);
       }
       else if(IsStr() && op.IsStr()) {
           string add = S + op.GetStr();
           return Value(add);
       }
       return Value();  
    }
      // subtract op from this
    Value operator-(const Value& op) const{
        if(IsInt() && op.IsInt() ){
            int sub = I - op.GetInt();
            return Value(sub);
        }
        else if(op.IsStr() && IsStr() ) {
            auto srch= S.find( op.GetStr() );
            string result = S;
            if( srch!= string::npos)
                result.erase(srch, op.GetStr().length());
            return result;            
        }
        return Value(); 
    }
    
    // multiply this by op
    Value operator*(const Value& op) const{
        if(IsInt() && op.IsInt() ){
            int mult = I * op.GetInt();
            return Value(mult);
        }
        else if(IsInt() && op.IsStr() ){
            
            if(I<0){
                throw( "Cannot multiply by a negative number");  
            }
            // return rptn(op.GetStr(), I);
            string temp;
            temp.reserve( I * op.GetStr().length() );
            for( int i=0; i<I; i++ )
                temp+= op.GetStr();
            return temp;
        }  
        else if(IsStr() && op.IsInt() ){
            int mult = op.GetInt();
            if(mult<0){
                throw ("Cannot multiply by a negative number");
            }
            // return rptn(S, op.GetInt());
            string temp;
            int In = op.GetInt();
            temp.reserve(In * S.length() );
            for( int i=0; i<In; i++ )
                temp+= S;
            return temp;
            
           
        }
        throw ("Type error on multiplication");
        return Value();
    }
    
    // divide this by op
    Value operator/(const Value& op) const{
        if(IsInt() && op.IsInt() ){
            int div = I/op.GetInt();
            return Value(div);
        }
        if(op.GetInt()==0){
            throw ("Divide by 0 error");
        }
        throw ("Type error on division");
        return Value();
    }
    
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) out << op.I;
        else if( op.IsStr() ) out << op.S;
        else out << "ERROR";
        return out;
    }
};

#endif