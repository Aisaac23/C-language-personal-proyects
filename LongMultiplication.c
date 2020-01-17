#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*The program receives as arguments, two unsigned integers

Example:

./longMultiplication 343456778384378290000000 34434999588887878867487736273762731116372
*/
int noArguments(int argc, char * argv[], char* version, char* author);
char* longMultiplication( char *factor1,  char *factor2);

int main(int argc, char* argv[])
{	char *result;
	/*unsigned long long i = 0;
	FILE * file = fopen("M82589933.txt","r");
	char c[2], *str;
	str = calloc(25000000, sizeof(char));
	while( i <  100000)
		if( ( c[0] = fgetc(file) ) == EOF )
			break;
		else if( c[0] != '\n')
		{
			str[i] = c[0];
			i++;
		}

	printf("\nCalculating...\n");
	result = longMultiplication(str, str);*/
	noArguments(argc, argv, "1.0", "Aisaac23");
	result = longMultiplication(argv[1], argv[2]);
	printf("\nResult: %s\n\n", result);
	
}

char* longMultiplication( char* factor1,  char* factor2)
{	
	unsigned long long f1Size = strlen(factor1), f2Size = strlen(factor2);
	unsigned long long resultSize = f1Size + f2Size;
	
	char *result; 
	unsigned int product = 0, prevCarry = 0, sumCarry = 0, carry = 0;
	
	// We need to prepare the space for normalized summands and the result... 
	result = calloc( resultSize+1, sizeof(char) );

	for(unsigned long long i = 0; i<resultSize; i++)
			result[i] = '0';
	result[resultSize] = '\0';
	
	unsigned long long longer, shorter, resultIndex, units;
	longer = f1Size >= f2Size ? f1Size : f2Size ;
	shorter = f2Size <= f1Size ? f2Size : f1Size ;
	units = 0;

	do
	{
		shorter--;
		resultIndex = (resultSize-1) - units;		
		do
		{
			// we get the product of the multiplication of two factors and its carry
			longer--;
			if( f1Size >= f2Size )
			{
				product = (factor1[longer]-'0') * (factor2[shorter]-'0');
				//printf("%c * %c = %u", factor1[longer], factor2[shorter], product);
			}
			else
			{	
				product = (factor1[shorter]-'0') * (factor2[longer]-'0');
				//printf("%c * %c = %u", factor1[shorter], factor2[longer], product);
			}
			carry = (product > 9) ? product/10 : 0;
			product -= carry*10;

			// we add the previous carry to the current product
			product += prevCarry;
			prevCarry = (product > 9) ? product/10 : 0;
			product -= prevCarry*10;
			// we add the previous result to the current one
			product += (result[resultIndex] - '0');
			sumCarry = (product > 9) ? product/10 : 0;
			product -= sumCarry*10;
			//We get the carry for the next operation
			prevCarry += (carry + sumCarry); 
			// we get the product of the multiplication of two factors and its carry
			result[resultIndex] = (char)(product + '0');
			resultIndex--; 
		}while( longer >=1 );
		result[resultIndex] = (char)(prevCarry + '0');
		prevCarry = 0;
		units++;
		longer = f1Size >= f2Size ? f1Size : f2Size ;

	}while( shorter >= 1 );
	//most of the times you'll have spare zeros in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 1)
		memmove(result, result+1, resultSize*sizeof(char)+1);

	return result;
}

int noArguments(int argc, char * argv[], char* version, char* author)
{
	if(argc <= 1)
	{
		printf("\n%s ver %s by %s\n", argv[0], version, author);
		exit(EXIT_SUCCESS);
	}
	else
		return 1;
}
