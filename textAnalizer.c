// Please find this program's description in the main function... 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <stdbool.h>

int noArguments(int argc, char * argv[], char* version, char* author);

typedef struct dataCharacteristics
{
	unsigned long long nLines; 
	unsigned long long nPrintableCharacters; 
	unsigned long long nNumbers; 
	unsigned long long nAlphabeticCharacters; 
	unsigned long long nWords;
	unsigned long long nSpecialChars;
	unsigned long long nSpaces;
	unsigned long long nWordsLowerThan4;
	unsigned long long nParagraphs;
	unsigned long long nWideChars;
	unsigned long long nWideWords;
	unsigned long long totalLength;
	
	wchar_t **allNumbers;
	wchar_t **allWords;
	wchar_t **allWideWords;
	wchar_t *allSpecialChars;
	
	
} data;

data * analyzeText(wchar_t* inputString, FILE *bigText, char *locale);

int main(int argc, char * argv[])
{	
	noArguments(argc, argv, "1.0", "Aisaac23");
	FILE *bigText = fopen(argv[1], "r");
	data *data1 = analyzeText(L"", bigText, "");
	fflush(stdout);
	
	
	//This program receives an UTF-8 formated text, and analyzes all its content and returns a pointer to structure with the following info: 
	wprintf(L"lines: %llu\n", data1->nLines);
	wprintf(L"n printable characters: %llu\n", data1->nPrintableCharacters);
	wprintf(L"n numbers: %llu\n", data1->nNumbers);
	wprintf(L"n alphapbetic characters: %llu\n", data1->nAlphabeticCharacters);
	wprintf(L"n words: %llu\n", data1->nWords);
	wprintf(L"n non-ASCII words: %llu\n", data1->nWideWords);
	wprintf(L"n special characters: %llu\n", data1->nSpecialChars);
	wprintf(L"n spaces: %llu\n", data1->nSpaces);
	wprintf(L"n words lower than 4 characters: %llu\n", data1->nWordsLowerThan4);
	wprintf(L"n paragraphs: %llu\n", data1->nParagraphs);
	wprintf(L"n wide chars: %llu\n", data1->nWideChars);
	wprintf(L"total length: %llu\n", data1->totalLength);
	
	wprintf(L"\nAll numbers found:\n");
	
	for(int index = 0; index<data1->nNumbers; index++)
		wprintf(L"%ls, ", data1->allNumbers[index]);
	
	wprintf(L"\nAll words found:\n");
	for(int index = 0; index<data1->nWords; index++)
		wprintf(L"%ls, ", data1->allWords[index]);

	wprintf(L"\nAll words with non-ASCII characters found:\n");
	for(int index = 0; index<data1->nWideWords; index++)
		wprintf(L"%ls, ", data1->allWideWords[index]);
	
	return EXIT_SUCCESS;
}

//Its' important to set a locale that anables UTF-8 and that the file is saved with UTF-8 encoding.
data* analyzeText(wchar_t* inputString, FILE *bigText, char *locale)
{	
	data *collection = (data*)calloc(1, sizeof(data));
	wchar_t ch[2], *mainString, *word, *toTokenize, **tokBuff, number[50];
	unsigned long long size = 0, index = 0;
	const unsigned int DEFAULT_SIZE = 10000, ASCII_MAX = 127;

	wint_t wc;
	bool hasWideChar = false;
	
	setlocale(LC_ALL, locale);

	collection->allNumbers = (wchar_t**)calloc(DEFAULT_SIZE, sizeof(wchar_t*));
	collection->allWords = (wchar_t**)calloc(DEFAULT_SIZE, sizeof(wchar_t*));
	collection->allWideWords = (wchar_t**)calloc(DEFAULT_SIZE, sizeof(wchar_t*));
	collection->allSpecialChars = (wchar_t*)calloc(DEFAULT_SIZE, sizeof(wchar_t));
	tokBuff = (wchar_t**)calloc(DEFAULT_SIZE, sizeof(wchar_t*));
	
	//validates if the text to analyze is a file or a string: 
	if( bigText != NULL)
	{
		while( (wc = fgetwc(bigText)) != WEOF )
		{
			if(wc > ASCII_MAX)
				collection->nWideChars++;
			size++;
		}
		mainString = calloc(size+1, sizeof(wchar_t));
	
		ch[1] = '\0';
			rewind(bigText);
		while((ch[0] = (wchar_t)fgetwc(bigText)) != EOF)
			mainString[index++] = ch[0];
		//if it's a file generates a string out of it
	}
	else
	{
		size = wcslen(inputString);
		mainString = calloc(size+1, sizeof(wchar_t));
		wcscpy(mainString, inputString);
		mainString[size] = L'\0';
	}
	
	collection->totalLength = size;
	toTokenize = calloc(size+1, sizeof(wchar_t));
	//this loop collects part of the numerical information:
	for(int i = 0; i < size; i++)
	{
		if( iswprint(mainString[i]) )
			collection->nPrintableCharacters++;
		if( iswalpha(mainString[i]) )
			collection->nAlphabeticCharacters++;
		if( iswpunct(mainString[i]) )
		{
			collection->allSpecialChars[collection->nSpecialChars] = mainString[i];
			collection->allSpecialChars[collection->nSpecialChars+1] = L'\0';
			collection->nSpecialChars++;
		}
		if( mainString[i] == L' ' )
			collection->nSpaces++;
		if( mainString[i] == L'\n' )
			collection->nLines++;
	}
	collection->allSpecialChars = realloc(collection->allSpecialChars, sizeof(wchar_t*)*(collection->nSpecialChars+1));
	
	wcscpy(toTokenize, mainString);
	wcscat(toTokenize, L"\0");
	
	word = wcstok(toTokenize, L" ", tokBuff);
	/* this loop collects all the individual words and the numbers found.
	It  deletes any format the number could have (e.g $12,000 is saved as 12000)*/
	while (word != NULL)
	{
		collection->allWords[collection->nWords] = realloc(collection->allWords[collection->nWords], (wcslen(word)+1)*sizeof(wchar_t));
		wcscpy(collection->allWords[collection->nWords], word);
		wcscat(collection->allWords[collection->nWords], L"\0");
		
		collection->nWords++;
		//This loop detects words that include any wide character and saves them in the next validation. 
		hasWideChar = false;		
		for(int i = 0; i<wcslen(word); i++)		
			if( ( (wint_t)word[i] ) > ASCII_MAX )
			{
				hasWideChar = true;
				i = wcslen(word);
			}

		if(hasWideChar)
		{
			collection->allWideWords[collection->nWideWords] = realloc(collection->allWideWords[collection->nWideWords], (wcslen(word)+1)*sizeof(wchar_t));
			wcscpy(collection->allWideWords[collection->nWideWords], word);
			wcscat(collection->allWideWords[collection->nWideWords], L"\0");

			collection->nWideWords++;
		}
		//counts words lower than four chars like: and, or, all, yes, etc, which may not be considered as words.		
		if( wcslen(word)<4 )
			collection->nWordsLowerThan4++;
		
		int index = 0;
		for(int i = 0; i<wcslen(word); i++)
			if( iswdigit( word[i]) || word[i] == L'.' || word[i] == L'-' || word[i] == L'+')
				number[index++] = word[i];
		number[index] = '\0';
		
		if( ( wcslen(number) > 0 && wcschr(number, L'.')==NULL ) || ( wcslen(number)>2 ) )
		{
			collection->allNumbers[collection->nNumbers] = realloc(collection->allNumbers[collection->nNumbers], ( wcslen(number)+1 )*sizeof(wchar_t) );
			wcscpy(collection->allNumbers[collection->nNumbers], number);
			wcscat(collection->allNumbers[collection->nNumbers], L"\0");
			collection->nNumbers++;
		}
		
		word = wcstok (NULL, L" ", tokBuff);
	}
	collection->allNumbers = realloc(collection->allNumbers, collection->nNumbers*sizeof(wchar_t*)+1 );
	collection->allWords = realloc(collection->allWords, collection->nWords*sizeof(wchar_t*)+1 );
	
	wcscpy(toTokenize, mainString);
	wcscat(toTokenize, L"\0");
	
	word = wcstok(toTokenize, L"\r\n",  tokBuff);
	//this loop counts the paragraphs:
	while (word != NULL)
	{	
		if( wcslen(word)>2 )
			collection->nParagraphs++;
		word = wcstok (NULL, L"\r\n", tokBuff);
	}
	
	return collection;
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
