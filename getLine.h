#include <assert.h>
#include <stdio.h>
#include <cstdio>

//-----------------------------------------------------------------------------------------------------------------

const int black   = 30;
const int red     = 31;
const int green   = 32;
const int yellow  = 33;
const int blue    = 34;
const int purple  = 35;
const int cyan    = 36;
const int white   = 37;
const int normal  = 39;

const int bblack  = 40;
const int bred    = 41;
const int bgreen  = 42;
const int byellow = 43;
const int bblue   = 44;
const int bpurple = 45;
const int bcyan   = 46;
const int bwhite  = 47;
const int bnormal = 49;

//-----------------------------------------------------------------------------------------------------------------

const int END = -1;

//-----------------------------------------------------------------------------------------------------------------

int getLine (char to [], int length); 
int reverse (char *in, int length);
int copy (char *from, char* to);
void printfcolour (char *text, int letters, int back); 
void printfcolouropen (char *text, int letters, int back);
void PrintArray (int* array, int size);

//-----------------------------------------------------------------------------------------------------------------

int getLine (char to [], int length)    {
	int c = 0, i = 0;

	for (i = 0; i < length && (c = getchar ()) != '\n' && c != '\0' && c != EOF; ++i)
		to [i] = c;
	if (i  >= length)    {
		assert (i == length);
		--i;
	}
	to [i] = '\0';
	
	if (c == EOF)    {
		putchar('\n');
		return END;
	}

	return i;
}

//-----------------------------------------------------------------------------------------------------------------

int reverse (char *in, int length)    {
	int i = 0;
	char backup [length + 1] = {};
	
	for (i = 0; i < length; ++i)
		backup [i] = in [length - 1 - i];
	assert (i == length);
	backup [i] = '\0';

	copy (backup, in);
}

//-----------------------------------------------------------------------------------------------------------------

int copy (char *from, char* to)    {
	int i = 0;
	while ((to [i] = from [i]) != '\0')
		++i;
	return i;
}

//-----------------------------------------------------------------------------------------------------------------

void printfcolour (char *text, int letters, int back) {
	printf ("\x1B" "[%dm" "\x1B" "[%dm" "%s" "\x1B" "[%dm" "\x1B" "[%dm", letters, back, text, normal, bnormal);
}

//-----------------------------------------------------------------------------------------------------------------

void printfcolouropen (char *text, int letters, int back) {
	printf ("\x1B" "[%dm" "\x1B" "[%dm" "%s", letters, back, text);
}

//------------------------------------------------------------------------------

void PrintArray (char* array, int size)
{		
		printf ("\n");
		for (int i = 0; i < size; i++)
				printf ("[%d] = %c, ", i, array[i]);
		printf ("END\n");
}


