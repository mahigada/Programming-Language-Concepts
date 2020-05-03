//Mahi Gada
//CS280
/*
Today we have a working system (assignment 3) that we want to add some new capability to (Value objects that we can perform operations on).
We want to make sure that this new piece of code works 100% before adding it to the system. 
We refer to this new functionality (Value) as a unit and we perform tests known as "unit tests".
For this assignment you should implement addition and subtraction for Value (that is, you should write Value::operator+(const Value& operand) and Value::operator-(const Value& operand). 
You should test to make sure that an assortment of combinations of Values and Value types generates correct answers.
You are GIVEN a header file (val.h from assignment 4; you can change it if you like, but there's no reason to do so).
You are GIVEN a main routine that tests your + and - functions and prints out results.
You MUST WRITE implementations of operator+ and operator- for Value. 
I suggest you put them in a file called val.cpp, and that you leave val.h unchanged.
It is not required for Lab 10, but I strongly suggest that you use the framework from this lab to implement operator* and operator/, and that you test out those two functions as well. 
This way if you know operations on Value work as a standalone unit, then you can be confident that they'll work inside of program 4.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "val.h"

void
doOp(const Value& a, const Value& b) {
	cout << a << " + " << b << " is " << flush << a + b << endl;
	cout << a << " - " << b << " is " << flush << a - b << endl;
}

int
main(int argc, char *argv[])
{
    Value a;
    Value b(3);
    Value c(4);
    Value d("hello");
    Value e("world");
    
    vector<Value> vals( {a,b,c,d,e} );
    
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "d=" << d << endl;
    cout << "e=" << e << endl;
    
    for(int i=0; i<5; i++ )
        for( int j=0; j<5; j++ )
            if( i != j )
                doOp( vals[i], vals[j] );
    
    return 0;
}
