#include <stdlib.h>
#include <stdio.h>

void print_cands (int cands [81] [9]);
int fill_cands (int* sudoku, int cands [81] [9]); 
void fill_horiz (int* sudoku, int y, int *cands);
void fill_verti (int* sudoku, int x, int *cands);
void fill_3x3 (int* sudoku, int x, int y, int *cands); 
void print_sudoku (int* sudoku, int step); 
int to_int (char* symbols, int* numbers); 
int sud_get (const char* path, char* buffer);
int determine (int cord);
int check_horiz (int* sudoku, int y, int cands [81] [9], const char type); 
int check_moves (int* sudoku, int cands [81] [9], const char type, int* UTM); //Unable To Move
 
const int FILE_SIZE =  150;
const int NOWHERE   = -666;
const int TRUE      =  228;
const int FALSE     =    0;

int main () {

    int UTM = FALSE;
    int where_put = NOWHERE;
    int step = 0;
    int sudoku [81] = {};
    int cands [81] [9] = {};
    char buffer [FILE_SIZE];

    sud_get ("sudoku.txt", buffer);
    to_int (buffer, sudoku);
    print_sudoku (sudoku, ++step);

    fill_cands (sudoku, cands);
    
    print_cands (cands);

    while (UTM == FALSE) {
        where_put = NOWHERE;

        if (where_put == NOWHERE)
            where_put = check_moves (sudoku, cands, 'o', &UTM);
        if (where_put == NOWHERE) 
            where_put = check_moves (sudoku, cands, 's', &UTM);
        
/*      if (where_put == NOWHERE)
            where_put = check_moves (sudoku, cands, "triple");  

        if (everything_filled (sudoku))
            break;
*/
        if (where_put != NOWHERE) { 
            print_sudoku (sudoku, step++);
            fill_cands (sudoku, cands);
        }   
    }
}
            
int sud_get (const char* path, char *buffer) {
    FILE * input;
    input = fopen (path, "r");
    fread (buffer, sizeof (char), FILE_SIZE, input);
    fclose (input);
    return 0;
}

int to_int (char* symbols, int* numbers) {
    for (int i = 0, j = 0; j < 81; ++i) {
        if (symbols [i] >= '0' && symbols [i] <= '9')
            numbers [j++] = (symbols [i] - '0');
    }
    return 0;
}
    
void print_sudoku (int* sudoku, int step) {
    printf ("\n>>> Step %d:\n\n", step);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j)
            printf("%d ", *(sudoku + 9 * i + j));
        printf ("\n\n");
    }
}

int fill_cands (int* sudoku, int cands [81] [9]) {
    for (int i = 0; i < 81; ++i) {
        int x = i % 9;
        int y = (i - x) / 9;
        
        if (sudoku [i] == 0) { 
            for (int j = 0; j < 9; ++j)
                cands [i] [j] = j + 1;

            fill_horiz (sudoku, y, cands [i]);
            fill_verti (sudoku, x, cands [i]);
            fill_3x3   (sudoku, x, y, cands [i]);
        }
        else
            for (int j = 0; j < 9; ++j)
                cands [i] [j] = 0;

    }
    return 0;
}

void fill_horiz (int* sudoku, int y, int *cands) {
    for (int i = 0; i < 9; ++i) {
        for (int x = 0; x < 9; ++x)
            if (sudoku [9 * y + x] == cands [i])
                cands [i] = 0;
    }
}
   
void fill_verti (int* sudoku, int x, int *cands) {
    for (int i = 0; i < 9; ++i) {
        for (int y = 0; y < 9; ++y)
            if (sudoku [9 * y + x] == cands [i])
                cands [i] = 0;
    }
}
 

void fill_3x3 (int* sudoku, int x, int y, int *cands) {
    int x_3x3 = determine (x);
    int y_3x3 = determine (y);

    for (int i = 0; i < 9; ++i)
        for (int ix = 0; ix < 3; ++ix)
            for (int iy = 0; iy < 3; ++iy)
                if (sudoku [9 * (y_3x3 + iy) + (x_3x3 + ix)] == cands [i])
                    cands [i] = 0;
}
 

void print_cands (int cands [81] [9]) {
    for (int i = 0; i < 81; ++i) {
        printf (">>> cands [%d]:\n", i);
        for (int j = 0; j < 9; ++j)
            printf("%d ", cands [i] [j]);
        printf ("\n\n");
    }
}

int determine (int cord) {
    switch (cord) {
    case 0:
    case 1:
    case 2:
        return 0;
        break;
    case 3:
    case 4:
    case 5:
        return 3;
        break;
    case 6:
    case 7:
    case 8:
        return 6;
        break;
    default:
        return -1;
    }
}

int check_moves (int* sudoku, int cands [81] [9], const char type, int* UTM) {
    for (int i = 0; i < 81; ++i) {
        int x = i % 9;
        int y = (i - x) / 9;
        int where_put = NOWHERE;
        
        if (where_put == NOWHERE)
            where_put = check_horiz (sudoku,    y, cands, type);
/*      if (where_put == NOWHERE)
            where_put = check_verti (sudoku, x,    cands, type);
        if (where_put == NOWHERE)
            where_put = check_3x3   (sudoku, x, y, cands, type);
*/
        if (where_put != NOWHERE) 
            return where_put;
    }
//    printf ("\n\n!!! STUCK !!!\n\n");
    *UTM = TRUE;
    return NOWHERE;
}

int check_horiz (int* sudoku, int y, int cands [81] [9], const char type) {
    int where_put = NOWHERE;
    int counter = 0;
    int putX = 777;
    int putNum = 888;
    switch (type) {
    case 'o': //obvious
        for (int x = 0; x < 9; ++x) {
            counter = 0;
            putNum = 0;
            for (int i = 0; i < 9; ++i)
                if (sudoku [9 * y + x]     == 0 &&
                    cands  [9 * y + x] [i] == i + 1) {
                    ++counter;
                    putNum = i;
                }
            if (counter == 1) {
                where_put = 9 * y + x;
                sudoku [9 * y + x] = putNum  + 1;
                break;
            } 
        }
        break;
    case 's': //single
        for (int i = 0; i < 9; ++i) {
            counter = 0;
            putX = 0;
            for (int x = 0; x < 9; ++x) 
                if (sudoku [9 * y + x]     == 0 &&
                    cands  [9 * y + x] [i] == i + 1) {
                    ++counter;
                    putX = x;
                }
            
            if (counter == 1) {
                where_put = 9 * y + putX;
                sudoku [9 * y + putX] = i + 1;
                break;
            }   
        }                    
        break;
    case 'p': //pair

        break;
    case 't': //triple
        
        break;
    default:
        printf ("WRONG ARG TO CHECK FUNC");
        return -2;
        break;
    }
    return where_put;
}
