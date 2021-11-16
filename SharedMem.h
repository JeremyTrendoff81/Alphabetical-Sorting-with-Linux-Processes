/**
 * @file SharedMem.h
 * @author Jeremy Trendoff - 101160306
 * @brief A header file to declare the shared_use_state struct.
 * @date 2021-10-30
 */

#ifndef SHARED_MEM_H
#define SHARED_MEM_H

/**
 * @brief The shared use state struct holding the char elements of the array, the sorted flag to designate when the array is sorted, and the semaphores for A3 and A5.
 */
typedef struct shared_use_state {
    char A1;
    char A2;
    char A3;
    char A4;
    char A5;
    char A6;
    char A7;

    int A3_semid;
    int A5_semid;

    int sorted;
} shared_use_state_t;

#endif