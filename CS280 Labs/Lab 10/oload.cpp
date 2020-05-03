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
