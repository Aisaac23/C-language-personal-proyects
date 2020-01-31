// Please find this program's description in the main function... 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <stdbool.h>
#include "chkops.h"

unsigned int minParagraphLenth = 2;
unsigned int minLengthByWord = 4;

void setMinWordLength(int len);
void setLocale(char *locale);
void setParagraphLength(int len);
wchar_t* loadData(FILE *bigText);

unsigned long long totalTextLength(wchar_t *mainString);
unsigned long long countPrintableCharacters(wchar_t *mainString);
unsigned long long countNonPrintableCharacters(wchar_t *mainString);
unsigned long long countDigits(wchar_t *mainString);
unsigned long long countAlphabeticCharacters(wchar_t *mainString);
unsigned long long countPunctuationCharacters(wchar_t *mainString);
unsigned long long countSpaces(wchar_t *mainString);
unsigned long long countLines(wchar_t *mainString);
unsigned long long countWideCharacters(wchar_t *mainString);
unsigned long long countWords( wchar_t mainString[] );
unsigned long long countSmallWords( wchar_t mainString[] );
unsigned long long countWideWords( wchar_t mainString[] );
unsigned long long countNumbers( wchar_t mainString[] );
unsigned long long countParagraphs( wchar_t mainString[] );
char *wideStringToString(wchar_t *wstring);

wchar_t *getPuntuationCharacters(wchar_t *mainString);
wchar_t **getWords( wchar_t mainString[] );
wchar_t **getWideWords( wchar_t mainString[] );
wchar_t **getNumbers( wchar_t mainString[] );
void setAvailableOptions(char *options[], char optionsString[]);
int menu(int nOps, char **options, int argc, char *argv[]);

int main(int argc, char * argv[])
{
	if(argc < 3)
	{
		printf("Arguments missing or with the wrong format in: %s\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	const int nOps = 22;
	char **options;
	char optionsString[] = "-file -locale -paragraph -wordLength -all -alpha -lines -punct -gWords -gWwords -digits -Wchars -length -white"\
				" -spaces -gPunct -sWords -paragraphs -numbers -words -Wwords -print";
	options = (char**) calloc( nOps, sizeof(char*) );
	setAvailableOptions(options, optionsString);
	
	menu(nOps, options, argc, argv);
	return EXIT_SUCCESS;
}

int menu(int nOps, char **options, int argc, char *argv[])
{
	
	for(int index = 0; index < argc; index++)
	{
		if(argv[index][0] == '-')
		{
			int selected = findMainOptions(nOps, options, argv[index]);
			switch(selected)
			{
				case 0:
					printf("%s\n", argv[index]);
				break;
				case 1:
					printf("%s\n", argv[index]);
				break;
				case 2:
					printf("%s\n", argv[index]);
				break;
				case 3:
					printf("%s\n", argv[index]);
				break;
				case 4:
					printf("%s\n", argv[index]);
				break;
				case 5:
					printf("%s\n", argv[index]);
				break;
				case 6:
					printf("%s\n", argv[index]);
				break;
				case 7:
					printf("%s\n", argv[index]);
				break;
				case 8:
					printf("%s\n", argv[index]);
				break;
				case 9:
					printf("%s\n", argv[index]);
				break;
				case 10:
					printf("%s\n", argv[index]);
				break;
				case 11:
					printf("%s\n", argv[index]);
				break;
				case 12:
					printf("%s\n", argv[index]);
				break;
				case 13:
					printf("%s\n", argv[index]);
				break;
				case 14:
					printf("%s\n", argv[index]);
				break;
				case 15:
					printf("%s\n", argv[index]);
				break;
				case 16:
					printf("%s\n", argv[index]);
				break;
				case 17:
					printf("%s\n", argv[index]);
				break;
				case 18:
					printf("%s\n", argv[index]);
				break;
				case 19:
					printf("%s\n", argv[index]);
				break;
				case 20:
					printf("%s\n", argv[index]);
				break;
				case 21:
					printf("%s\n", argv[index]);
				break;
				case 22:
					printf("%s\n", argv[index]);
				break;
			}
		}
	}
	return 1;
}

void setAvailableOptions(char **options, char optionsString[])
{
	char *op;
	int len;
	op = strtok(optionsString, " ");
	while(op != NULL)
	{
		len = strlen(op);
		*(options) = calloc( len+1, sizeof(char) );
		strcpy( *(options) , op);
		(*(options))[len] = '\0';
		options++;
		op = strtok(NULL, " ");
	}
	return;
}

wchar_t* loadData(FILE *bigText)
{
	wchar_t ch[2], *fileString = NULL;
	wint_t wc = 0;
	unsigned long long size = 0;

	if( bigText != NULL)
	{
		while( (wc = fgetwc(bigText)) != EOF )
			size++;

		fileString = calloc( size+1, sizeof(wchar_t) );
	
		ch[1] = '\0';
		rewind(bigText);
		
		size = 0;
		while( (ch[0] = (wchar_t)fgetwc(bigText)) != EOF )
			fileString[size++] = ch[0];
		fileString[size] = L'\0';
	}

	return fileString;
}

void setLocale(char *locale)
{
	setlocale(LC_ALL, locale);
}

void setParagraphLength(int len)
{
	minParagraphLenth = len;
}

void setMinWordLength(int len)
{
	minLengthByWord = len;
}

unsigned long long totalTextLength(wchar_t *mainString)
{
	return wcslen(mainString);
}

unsigned long long countPrintableCharacters(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( iswprint( mainString[i] ) )
			count++;
	return count;
}

unsigned long long countNonPrintableCharacters(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( !iswprint( mainString[i] ) )
			count++;
	return count;
}

unsigned long long countDigits(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( isdigit( mainString[i] ) )
			count++;
	return count;
}

unsigned long long countAlphabeticCharacters(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( iswalpha( mainString[i] ) )
			count++;
	return count;
}

unsigned long long countPunctuationCharacters(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( iswpunct( mainString[i] ) )
			count++;
	return count;
}

wchar_t * getPuntuationCharacters(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	wchar_t *chars;
	
	count = countPunctuationCharacters(mainString);
	chars = (wchar_t*)calloc( count+1, sizeof(wchar_t) );

	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( iswpunct( mainString[i] ) )
			chars[count] = mainString[i];
	return chars;
}

unsigned long long countSpaces(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( mainString[i] == L' ' )
			count++;
	return count;
}

unsigned long long countLines(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( mainString[i] == L'\n' )
			count++;
	return count;
}

unsigned long long countWideCharacters(wchar_t *mainString)
{
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	for(unsigned long long i = 0; i < length; i++)
		if( ((wint_t)mainString[i]) > ASCII_MAX )
			count++;
	return count;
}

unsigned long long countWords( wchar_t *mainString )
{
	wchar_t *word, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );	
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';

	word = wcstok(toMakeTokens, L" ", tokBuff);
	while( word != NULL )
	{
		count++;
		word = wcstok (NULL, L" ", tokBuff);
	}
	return count;	
}

unsigned long long countSmallWords( wchar_t *mainString )
{
	wchar_t *word, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';

	word = wcstok(toMakeTokens, L" ", tokBuff);
	while( word != NULL )
	{
		if( wcslen(word) < minLengthByWord )
			count++;
		word = wcstok (NULL, L" ", tokBuff);
	}
	
	return count;	
}

unsigned long long countWideWords( wchar_t *mainString )
{
	wchar_t *word, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';

	word = wcstok(toMakeTokens, L" ", tokBuff);
	while( word != NULL )
	{
		if( hasWideChars(word) )
			count++;
		word = wcstok (NULL, L" ", tokBuff);
	}
	
	return count;	
}


/*NOTICE: getWords() IS dependent of countWords () */
wchar_t **getWords( wchar_t *mainString )
{	
	wchar_t *word, **allWords, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';

	count  = countWords(mainString);
	allWords = (wchar_t **)calloc( count+1, sizeof(wchar_t*) );	
	
	word = wcstok(toMakeTokens, L" ", tokBuff);
	count = 0;
	while( word != NULL )
	{
		wcscpy( allWords[count], word );
		word = wcstok (NULL, L" ", tokBuff);
		count++;
	}
	allWords[count] = NULL;

	return allWords;
}

/*NOTICE: getWideWords() IS dependent of countWords () */
wchar_t **getWideWords( wchar_t *mainString )
{	
	wchar_t *word, **allWideWords, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';
	
	count  = countWideWords(mainString);
	allWideWords = (wchar_t **)calloc( count+1, sizeof(wchar_t*) );	
	
	word = wcstok(toMakeTokens, L" ", tokBuff);
	count = 0;
	while( word != NULL )
	{
		if( hasWideChars(word) )
			wcscpy( allWideWords[count++], word );

		word = wcstok (NULL, L" ", tokBuff);
	}
	allWideWords[count] = NULL;

	return allWideWords;
}

wchar_t **getNumbers( wchar_t *mainString )
{	
	wchar_t *word, **allNumbers, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';
	
	count  = countWords(mainString);
	allNumbers = (wchar_t **)calloc( count+1, sizeof(wchar_t*) );	
	
	word = wcstok(toMakeTokens, L" ", tokBuff);
	count = 0;
	while( word != NULL )
	{
		if( isUnsignedNumber( wideStringToString(word) ) || isSignedNumber( wideStringToString(word) ) )
			wcscpy( allNumbers[count++], word );

		word = wcstok (NULL, L" ", tokBuff);
	}
	allNumbers[count] = NULL;

	return allNumbers;
}

unsigned long long countNumbers( wchar_t *mainString )
{
	wchar_t *word, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';

	word = wcstok(toMakeTokens, L" ", tokBuff);
	while( word != NULL )
	{
		if( isUnsignedNumber( wideStringToString(word) ) || isSignedNumber( wideStringToString(word) ) )
			count++;
		word = wcstok (NULL, L" ", tokBuff);
	}
	
	return count;	
}

unsigned long long countParagraphs( wchar_t *mainString )
{
	wchar_t *paragraph, **tokBuff, *toMakeTokens;
	unsigned long long count = 0, length;
	
	length = wcslen(mainString);
	tokBuff = (wchar_t**)calloc(1, sizeof(wchar_t*));
	toMakeTokens = (wchar_t*)calloc(length, sizeof(wchar_t) );
	wcscpy(toMakeTokens, mainString);
	toMakeTokens[length] = '\0';

	paragraph = wcstok(toMakeTokens, L"\n",  tokBuff);
	while (paragraph != NULL)
	{	
		if( wcslen(paragraph) >= minParagraphLenth )
			count++;
		paragraph = wcstok (NULL, L"\n", tokBuff);
	}
	return count;
}

/*NOTICE: this function is not safe if you there are non-ASCII characters in the passed string.*/
char *wideStringToString(wchar_t *wstring)
{
	unsigned long long length = wcslen( wstring );
	char *buffer;
	
	buffer = calloc( length, sizeof(char) );
	for(unsigned long long index = 0; index < length; index++)
		buffer[index] = (char)wctob(wstring[index]);	
	return buffer;		
}

