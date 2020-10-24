#include "uberonegin.h"

int main () {
    FILE *hamlet, *sorted_out;
    struct stat file_info;
    char path            [] = "hamlet.txt";
    char text_sorted_out [] = "005HAMLET_SORTED.txt";

    size_t size   = 0;
    size_t nLines = 1;


    stat (path, &file_info);
    size = file_info.st_size;
    
    printf ("The size of %s is equal to %d bytes\n", path, size);
    char* buffer = calloc (size, sizeof(char));

    hamlet = fopen (path, "r");
    fread (buffer, size, sizeof(char), hamlet);
    fclose (hamlet); 

    for (size_t i = 0; buffer [i]; ++i)
        if (buffer [i] == '\n')
            ++nLines;

    printf ("nLines = %d\n", nLines);

    Line* text = calloc (nLines + 1, sizeof (Line));

    n_to_0 (buffer, size);
    fill_text (buffer, text, size);
   
    printf ("I'm about to sort\n"); 
    ney_qsort (text, 0, nLines - 1);
    
    for (int i = 0; i < nLines; ++i)
        blankfix (text [i]);

    print_text (sorted_out, text_sorted_out, text, nLines);
    
    free (buffer);
    free (text);
}
