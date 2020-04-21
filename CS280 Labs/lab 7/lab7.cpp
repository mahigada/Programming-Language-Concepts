/*
You are given a text file, recurDEMO.txt, which contains some code samples from the slides for this lab.
Write a version of a recursive Fibonacci number calculator to calculate the Nth Fibonacci number. The function should
count the total number of times that it is called
count the total number of times that it is called for a particular value of N
Run the program to calculate fib(20). Count how many times the fib function is called, and how many times it is called when N is equal to 7 and when N is equal to 3.
There should be two lines of output generated: one for fib(20) when N is 7 and one for fib(20) when N is 3. 
The format of the output line should be:
fib(N) called X times, total Y
where N is 7 or 3, X is the number of times fib(N) is called, and Y is the total calls to fib.
NEXT, generate a new version of fib (call it fib2) that uses a cache of the first ten Fibonacci numbers. 
You can keep the cache in any convenient form, and you should pre-load the cache before using the new function.
Have the new version count the number of times that the function is called when it cannot fetch a value from the cache (so, fib(5) would fetch an answer from the cache and would report a 0. 
However, fib(10) would report 1 call (which would in turn call fib(9) and fib(8), in the cache).
The resulting output line from this run would be a single line:
fib2(20) called X times
Run and time both versions of the function when it calculates fib(20). 
Call each version of the function 1000 times, and print out the timing result to see the advantage of precalculation and caching.
*/
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
