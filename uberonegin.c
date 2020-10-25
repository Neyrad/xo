#include "uberonegin.h"

int main () {
    FILE *hamlet, *sorted;
    struct stat file_info;
    char path     [] = "hamlet.txt";
    char path_out [] = "328rhyme.txt";

    size_t size   = 0;
    size_t nLines = 0;

    stat (path, &file_info);
    size = file_info.st_size;
    
    printf ("The size of %s is equal to %d bytes\n", path, size);
    char* _buffer = (char*) calloc (1, size * sizeof(char) + 2 * sizeof(int));
    *((int*)_buffer) = CANARY;
    *((int*)((char*)((int*)_buffer + 1) + size)) = CANARY;

    char* buffer = (char*)((int*)_buffer + 1);
    buffer_assert (_buffer, size);

    hamlet = fopen (path, "r");
    fread (buffer, size, sizeof(char), hamlet);
    fclose (hamlet);

    for (size_t i = 0; buffer [i]; ++i)
        if (buffer [i] == '\n')
            ++nLines;

    printf ("nLines = %d\n", nLines);

    Line* _text = (Line*) calloc (1, nLines * sizeof(Line) + 2 * sizeof(int));
    *((int*)_text) = CANARY;
    *((int*)((Line*)((int*)_text + 1) + nLines)) = CANARY;

    Line* text = (Line*)((int*)_text + 1);
    text_assert (_text, nLines);

    n_to_0 (buffer, size);
    fill_text (buffer, text, size, nLines);
   
    printf ("I'm about to sort\n"); 
    ney_qsort (text, 0, nLines - 1, nLines);
    
    for (int i = 0; i < nLines; ++i)
        blankfix (text [i]);

    print_text (sorted, path_out, text, nLines);
    
    free (_buffer);
    free (_text);
}
