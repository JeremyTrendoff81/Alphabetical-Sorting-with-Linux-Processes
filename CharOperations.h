/**
 * @file CharOperations.h
 * @author Jeremy Trendoff - 101160306
 * @brief Char Operations for Assignment 2 of SYSC4001A. 
 */

#ifndef CHAR_OPERATIONS_H
#define CHAR_OPERATIONS_H

#include "SharedMem.h"

/**
 * @brief Assign an integer sortable value to a char. 
 * 
 * @param c The char to assign a value.
 * @return int The assigned value.
 */
int assign_value(char c);

/**
 * @brief Get the char from the assigned value. 
 * 
 * @param i The int to convert.
 * @return char The char fetched.
 */
char get_char_from_value(int i);

/**
 * @brief Sort a segment of length 3.
 * 
 * @param arr The segment to sort.
 * @return char* A pointer to the resulting sorted segment. 
 */
char* sort_segment(char arr[3]);

/**
 * @brief Check if an array is sorted.
 * 
 * @param arr The array.
 * @param n The length of the array.
 * @return int 0 if not, 1 if sorted.
 */
int sorted(char* arr, int n);

/**
 * @brief Print a character array to the console.
 * 
 * @param arr The array.
 * @param n The length of the array.
 */
void print_char_array(char* arr, int n);

/**
 * @brief Print the shared array from a shared use state.
 * 
 * @param sus The shared use state to print.
 */
void print_shared_array(shared_use_state_t sus);

#endif