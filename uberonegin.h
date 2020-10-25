#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct _line {
    char* start;
    char* end;
};

const int CANARY = 17;
const int ERROR = 777;

typedef struct _line Line;

void n_to_0 (char* buffer, size_t size);
void fill_text (char* buffer, Line* text, size_t size, size_t nLines);
void print_text (FILE *out, const char* path, Line* text, size_t nLines);
int my_strcmp (const char* strA, const char* strB);
void swap (Line* array, size_t i, size_t j);
int isLetter (char symbol);
size_t partition (Line* array, size_t start, size_t end, size_t nLines);
void ney_qsort (Line* array, size_t start, size_t end, size_t nLines); 
int blankfix (Line str);
int isBlank (char* string); 
int rhyme_strcmp (const char* strA, const char* strB);
void text_assert (Line* _text, size_t nLines);
void buffer_assert (char* _buffer, size_t size);


void n_to_0 (char* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
//      printf ("i = %d, can't see n\n", i);
        if (buffer [i] == '\n') {
//          printf ("I'm about to write 0 instead of n, buffer [%d] = <%c>\n",
//                                                              i,   buffer [i]);
            buffer [i] = '\0';
        }
    }
}

void fill_text (char* buffer, Line* text, size_t size, size_t nLines) {
    text [0].start = buffer;

    for (size_t i = 0, k = 0; i < size && k < nLines; ++i)
        if (buffer [i] == '\0') {
//          printf ("I'm about to increment k (k = %d)...\n", k);
            text [k].end = &buffer [i - 1]; //the end of the line
            if (buffer [i + 1] != CANARY)    //change to canary
                text [k + 1].start = &buffer [i + 1]; //the start of the new line
        ++k;
    }
}

void print_text (FILE *out, const char* path, Line* text, size_t nLines) {
    
    out = fopen (path, "w");
    
    for (size_t i = 0; i < nLines; ++i) { //why nLines - 1?
//      printf ("Printing the %d line... \n", i);
        if (!isBlank (text [i].start))
            fprintf (out, "%s\n", text [i].start);//prints even members of the text []
    }

    fclose (out);
}

int my_strcmp (const char* strA, const char* strB) {

	int counter = 0;
	int shiftA = 0;
	int shiftB = 0;
//  printf ("strB = %p\n", strB);
	for (shiftA = 0; !isLetter (*(strA + shiftA))
	       						  && *(strA + shiftA) != '\0'; ++shiftA);
	for (shiftB = 0; !isLetter (*(strB + shiftB))
								  && *(strB + shiftB) != '\0'; ++shiftB);			
		


	for (counter = 0; *(strA + shiftA + counter) != '\0' 
		 	 	   && *(strB + shiftB + counter) != '\0'; ++counter) {
		
	
		if      (*(strA + shiftA + counter) < *(strB + shiftB + counter))
			return -1;
		else if (*(strA + shiftA + counter) > *(strB + shiftB + counter))
			return  1;
	}

	if      (*(strA + shiftA + counter) == '\0'
		  && *(strB + shiftB + counter) == '\0')
		return  0;
	else if (*(strA + shiftA + counter) == '\0')
		return -1;
	else if (*(strB + shiftB + counter) == '\0')
		return  1;
	else
		return ERROR;
}

int isLetter (char symbol) {
//    printf ("isLetter? <%c>\n", symbol);
    return (symbol >= 'A' && symbol <= 'Z'
         || symbol >= 'a' && symbol <= 'z') ? 1 : 0;
}

size_t partition (Line* array, size_t start, size_t end, size_t nLines) {
    Line pivot = array [end];
    size_t pindex = start;

    text_assert ( (int*)array - 1, nLines);
    for (size_t i = start; i < end; ++i) {
 //       if (rhyme_strcmp (array [i].end, pivot.end) == ERROR)
 //           printf ("STRCMP RETURNED ERROR\n");
        if (rhyme_strcmp (array [i].end, pivot.end) <= 0)
            swap (array, i, pindex++);
    }
    swap (array, end, pindex);
//  printf ("Partition (): successful. returning pindex = %d\n", pindex); 
    return pindex;
}

void swap (Line* array, size_t i, size_t j) {
    if (i == j)
        return;

    Line temp = array [i];
    array [i] = array [j];
    array [j] = temp;
}

void ney_qsort (Line* array, size_t start, size_t end, size_t nLines) {
//  printf ("Starting qsort()...\n");
    if (start < end) {
        size_t pindex = partition (array, start, end, nLines);
        ney_qsort (array, start, pindex - 1, nLines);
        ney_qsort (array, pindex + 1, end, nLines);
    }
}

int blankfix (Line str) {
	int start = 0, counter = 0;
	char* buffer = (char*) calloc (str.end - str.start + 2, sizeof (char));

	for (int i = 0; *(str.start + i) != '\0'; ++i) {
		if         (*(str.start + i) == '\t'
                 || *(str.start + i) == ' ')
			start = i + 1;
		else
			break;
	}

	for (counter = 0; *(str.start + start + counter) != '\0'; ++counter)
	 	*(buffer + counter) = *(str.start + start + counter);
	*(buffer + counter) = '\0';
	
	for (int i = 0; (*(str.start + i) = *(buffer + i)) != '\0'; ++i);
	
	free (buffer);
	return start;
}

int isBlank (char* string) {
	int counter = 0, blanks = 0;
	for (counter = 0; *(string + counter) != '\0'; ++counter)
		if (*(string + counter) == ' '
	    ||  *(string + counter) == '\t'
	    ||  *(string + counter) == '\n')
			++blanks;
	return blanks == counter;
}

int rhyme_strcmp (const char* strA, const char* strB) {

//   printf ("Starting rhyme_strcmp ()...\n");

	int counter = 0;
	int shiftA = 0;
	int shiftB = 0;
    
//  printf ("*strA = %c\n", *strA);
//  printf ("strA = %p, strB = %p\n", strA, strB);

	for (shiftA = 0; !isLetter (*(strA - shiftA))
	              && *(strA - shiftA) != '\0'; ++shiftA);
//  printf ("shiftA = %d\n", shiftA);
//  printf ("alive\n");
	for (shiftB = 0; !isLetter (*(strB - shiftB))
		          && *(strB - shiftB) != '\0'; ++shiftB);
//  printf("shiftB = %d\n", shiftB);	
//  printf ("still alive\n");

	for (counter = 0; *(strA - shiftA - counter) != '\0' 
		 	 	   && *(strB - shiftB - counter) != '\0'; ++counter) {
	
		if      (*(strA - shiftA - counter) < *(strB - shiftB - counter))
			return -1;
		else if (*(strA - shiftA - counter) > *(strB - shiftB - counter))
			return  1;
	}

	if      (*(strA - shiftA - counter) == '\0'
		  && *(strB - shiftB - counter) == '\0')
		return  0;
	else if (*(strA - shiftA - counter) == '\0')
		return -1;
	else if (*(strB - shiftB - counter) == '\0')
		return  1;
	else
		return ERROR;
}


void buffer_assert (char* _buffer, size_t size) {    
    assert (*((int*)_buffer) == CANARY &&
    *((int*)((char*)((int*)_buffer + 1) + size)) == CANARY);
}


void text_assert (Line* _text, size_t nLines) {   
    assert (*((int*)_text) == CANARY &&
    *((int*)((Line*)((int*)_text + 1) + nLines)) == CANARY);
}
