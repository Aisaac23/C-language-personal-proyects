#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "chkops.h"
/*Three useful functions that helps you validate your passed arguments to main but you can also use them to validate some other variables.

int findMainOptions( int optionsCount, char *availableOptions[], char *chosenOption );
bool isNumber(char* number);
bool fileExists(char* fileName);
bool areLettersOnly(char* word);
*/
int main(int argc, char * argv[])
{	

	char *programOptions[4];
	int op;	

	programOptions[0] = "-open";
	programOptions[1] = "-close"; 
	programOptions[2] = "-read";
	programOptions[3] = "-write";
	
	op = findMainOptions(4, programOptions, argv[1]);
	printf("%i\n", op);	
	
	printf("%i\n", isNumber(argv[2]) );
	printf("%i\n", fileExists(argv[3]) );
	printf("%i\n", areLettersOnly( argv[4] ) );	

	return EXIT_SUCCESS;
}
/*
//Checks in a list of available options if the chosen one exists.
int findMainOptions( int optionsCount, char *availableOptions[], char *chosenOption )
{
	for(int index = 0; index < optionsCount; index++)
		if( strcmp( availableOptions[index], choosenOption) == 0 )
			return index;
	return -1;
}

//Checks if the passed number (as string) is a valid integer or float type of number.
bool isNumber(char* number)
{
	int len = strlen(number);
	bool point = false;
	for( int index = 0; index < len; index++ )
		if( !isdigit(number[index]) )
		{
			if( !point && number[index] == '.' && index != 0 && index != len)
				point = true;
			else
				return false;
		}
	return true;		
}

//Checks if the passed file name exists and if it exists also checks if it can be opened.
bool fileExists(char* fileName)
{
	FILE *tempFile;
	tempFile = fopen( fileName, "r");
	if( tempFile == NULL )
		return false;
	else
		fclose(tempFile);
	return true;
}

//Checks if the passed word consists only of letters and returns false on any occurrence of any other character. 
bool areLettersOnly(char* word)
{
	int len = strlen(word);
	for( int index = 0; index < len; index++ )
		if( !isalpha(word[index]) )
			return false;
	return true;		
}*/
