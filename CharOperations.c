/**
 * @file CharOperations.c
 * @author Jeremy Trendoff - 101160306
 * @brief Th implemtation of the CharOperations header file.
 */

#include "CharOperations.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Assign an integer sortable value to a char. This is not a good solution, but it'll get the job done.
 * 
 * @param c The char to assign a value.
 * @return int The assigned value.
 */
int assign_value(char c)
{
    switch (c)
    {
    case 'A':
        return 0;

    case 'a':
        return 0;

    case 'B':
        return 1;

    case 'b':
        return 1;

    case 'C':
        return 2;

    case 'c':
        return 2;

    case 'D':
        return 3;

    case 'd':
        return 3;

    case 'E':
        return 4;

    case 'e':
        return 4;

    case 'F':
        return 5;

    case 'f':
        return 5;

    case 'G':
        return 6;

    case 'g':
        return 6;

    case 'H':
        return 7;

    case 'h':
        return 7;

    case 'I':
        return 8;

    case 'i':
        return 8;

    case 'J':
        return 9;

    case 'j':
        return 9;

    case 'K':
        return 10;

    case 'k':
        return 10;

    case 'L':
        return 11;

    case 'l':
        return 11;

    case 'M':
        return 12;

    case 'm':
        return 12;

    case 'N':
        return 13;

    case 'n':
        return 13;

    case 'O':
        return 14;

    case 'o':
        return 14;

    case 'P':
        return 15;

    case 'p':
        return 15;

    case 'Q':
        return 16;

    case 'q':
        return 16;

    case 'R':
        return 17;

    case 'r':
        return 17;

    case 'S':
        return 18;

    case 's':
        return 18;

    case 'T':
        return 19;

    case 't':
        return 19;

    case 'U':
        return 20;

    case 'u':
        return 20;

    case 'V':
        return 21;

    case 'v':
        return 21;

    case 'W':
        return 22;

    case 'w':
        return 22;

    case 'X':
        return 23;

    case 'x':
        return 23;

    case 'Y':
        return 24;

    case 'y':
        return 24;

    case 'Z':
        return 25;

    case 'z':
        return 25;
    
    default:
        return 100;
    }
}

/**
 * @brief Get the char from the assigned value. This is not a good solution, but it'll get the job done.
 * 
 * @param i The int to convert.
 * @return char The char fetched.
 */
char get_char_from_value(int i)
{
    switch (i)
    {
    case 0:
        return 'a';

    case 1:
        return 'b';
    
    case 2:
        return 'c';

    case 3:
        return 'd';

    case 4:
        return 'e';

    case 5:
        return 'f';

    case 6:
        return 'g';

    case 7:
        return 'h';

    case 8:
        return 'i';

    case 9:
        return 'j';

    case 10:
        return 'k';

    case 11:
        return 'l';

    case 12:
        return 'm';

    case 13:
        return 'n';

    case 14:
        return 'o';

    case 15:
        return 'p';

    case 16:
        return 'q';

    case 17:
        return 'r';

    case 18:
        return 's';

    case 19:
        return 't';

    case 20:
        return 'u';

    case 21:
        return 'v';

    case 22:
        return 'w';

    case 23:
        return 'x';

    case 24:
        return 'y';

    case 25:
        return 'z';
    
    default:
        return '?';
    }
}

/**
 * @brief Sort a segment of length 3.
 * 
 * @param arr The segment to sort.
 * @return char* A pointer to the resulting sorted segment. 
 */
char* sort_segment(char arr[3])
{
    int sorting_arr[3];

    for (int i = 0; i < 3; i++)
    {
        sorting_arr[i] = assign_value(arr[i]);
    }

    for (int c = 0; c < 3 - 1; c++)
    {
        for (int d = 0; d < 3 - c - 1; d++)
        {
            if (sorting_arr[d] > sorting_arr[d + 1])
            {
                int swap = sorting_arr[d];
                sorting_arr[d] = sorting_arr[d + 1];
                sorting_arr[d + 1] = swap;
            }
        }
    }

    char* return_arr = malloc(3 * sizeof(char));

    for (int i = 0; i < 3; i++)
    {
        return_arr[i] = get_char_from_value(sorting_arr[i]);
    }

    return return_arr;
}

/**
 * @brief Check if an array is sorted.
 * 
 * @param arr The array.
 * @param n The length of the array.
 * @return int 0 if not, 1 if sorted.
 */
int sorted(char* arr, int n)
{
    int sorting_arr[n];

    for (int i = 0; i < n; i++)
    {
        sorting_arr[i] = assign_value(arr[i]);
    }

    for (int i = 0; i < (n - 1); i++)
    {
        if (sorting_arr[i] > sorting_arr[i + 1]) 
        {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Print a character array to the console.
 * 
 * @param arr The array.
 * @param n The length of the array.
 */
void print_char_array(char *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i < (n - 1))
        {
            printf("%c ", arr[i]);
        }
        else
        {
            printf("%c\n", arr[i]);
        }
    }
}

/**
 * @brief Print the shared array from a shared use state.
 * 
 * @param sus The shared use state to print.
 */
void print_shared_array(shared_use_state_t sus)
{
    printf("%c %c %c %c %c %c %c\n", sus.A1, sus.A2, sus.A3, sus.A4, sus.A5, sus.A6, sus.A7);
}
