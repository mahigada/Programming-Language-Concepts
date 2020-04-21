#include <iostream>
using namespace std;

#include <chrono>

using namespace std::chrono;

const int samples =100;
int count7 =0;
int count3 = 0;
int countfib = 0;
int countfib2 = 0;
int fibs [10];

int fib(unsigned int n) {
    countfib++;
	if( n < 2 ) return n;
    if (n==3) count3++;
    if (n==7) count7++;
    return fib(n-1) + fib(n-2);
}
int fib2(unsigned int n) {
    if (n<10) return fibs[n];
    countfib2++;
    return fib2(n-1) + fib2(n-2);
}

int
main(int argc, char *argv[])
{
    fib(20);
    cout<<"fib(7) called " << count7 << " times, total "<<countfib<<endl;
	cout<<"fib(3) called " << count3 << " times, total "<<countfib<<endl;
    for( int s = 0; s < 10; s++ ){
        fibs[s]=fib(s);        
    }
    fib2(20);
    cout<<"fib2(20) called " << countfib2 << " times"<<endl;
    return 0;
}