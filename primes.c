#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/*This program takes as an argument a positive integer number and returns an array with all the prime numbers less than or equal.
After the function "allPrimes" returns, the program shows 20 randomly selected primes from the array returned. 
Important note: the function stores the prime numbers from position 1 of the array, saving in position 0 the total number of primes found.

Example: primes 1844674407

output:
To find and store: 10264907 prime numbers it took... 1465 seconds

Here are 20 randomly taken from the array:
9247913
...
67637431
53918593
*/

void delay(unsigned int seconds);
unsigned long long* allPrimes(unsigned long long top);

int main(int argc, char* argv[])
{
	time_t timer, timer2;
	double seconds;
	const int SHOW = 20;
	unsigned long long *primes; 

	time(&timer);  /* get current time; same as: timer = time(NULL)  */
	primes = allPrimes((unsigned long long)atoi(argv[1]) );
	
	time(&timer2);
	printf("To find and store: %llu prime numbers it took... ", primes[0]);    
	seconds = difftime(timer2,timer);
	printf ("%.f seconds\n\n", seconds);
	
	printf ("Here are the first %i primes:\n", SHOW);
	for(int i = 1; i<=SHOW; i++)
		printf("%llu, ", primes[i]);

	printf ("Here are %i randomly taken from the array:\n", SHOW);
	
	srand (time(NULL));
	for(int i = 0; i<SHOW; i++)
	{
		delay(1);
		printf("%llu\n", primes[ rand()%(primes[0]-1)+1 ]);
	}
	
	return 0;
}

void delay(unsigned int seconds)
{
	clock_t tOneScond, tCounter;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	while(tCounter < tOneScond)
		tCounter = clock();
}

unsigned long long* allPrimes(unsigned long long top)
{
	unsigned long long n = 2, divisor, nPrimes;
	unsigned long long *primes;
	bool isPrime = true;
	
	primes = calloc(top, sizeof(unsigned long long) );
	
	while(n < top)
	{
		divisor = 5; /* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers
can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
		if(n <= 3 )
			isPrime = true;
		else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3
			isPrime = false;
		else
			while(isPrime && divisor*divisor <= n)/* we need only integer divisors less than or equal sqroot(n). Factors greater than that will result in a number always lower than n or always greater. */
			{
				if(n%divisor == 0 || n%(divisor+2) == 0 ) // if it can be divided by divisor or if divisor is even 
					isPrime = false;
				else
					divisor+=6;
			}

		if(isPrime)
			primes[nPrimes++] = n;
		n++;
		isPrime=true;		
	}
	primes[0] = nPrimes;
	return primes;
}
