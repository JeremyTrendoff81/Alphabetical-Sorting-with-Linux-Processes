/**
 * @file CSORT.c
 * @author Jeremy Trendoff
 * @brief Assignment 2 for SYSC4001A.
 */

// Include statements for program.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

// Header files for program.
#include "semun.h"
#include "SharedMem.h"
#include "CharOperations.h"
#include "semaphore.h"

/**
 * @brief The main method.
 */
int main(int argc, char const *argv[])
{
    // 0 = no debug mode, 1 = debug mode.
    int debug_mode;

    /* Initialize debug mode. */

    if (argc == 2)
    {
        if (strcmp(argv[1], "-d") == 0)
        {
            debug_mode = 1;
        } else if (strcmp(argv[1], "--debug") == 0)
        {
            debug_mode = 1;
        } else
            debug_mode = 0;
    } else 
        debug_mode = 0;

    /* Initialize shared memory */

    // The shared use state.
    shared_use_state_t *shared_stuff;
    void *shared_memory = (void *)0;
    int shmid;

    // Creating shared memory ID and attaching shared memory segment to child process
    shmid = shmget((key_t)1234, sizeof(shared_use_state_t), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    shared_stuff = (shared_use_state_t *)shared_memory; 

    // pid for the process responsible for initializing the array of letters.
    pid_t pid;

    // pid of process handling A[1] to A[3].
    pid_t pid1;

    // pid of process handling A[3] to A[5].
    pid_t pid2;

    // pid of process handling A[5] to A[7].
    pid_t pid3;

    // pid to check when the array is fully sorted.
    pid_t pid4;

   /* Run the process to initialize the shared use state. */

    pid = fork();
    switch (pid)
    {
    case -1:
        perror("Fork Failed for pid");
        exit(EXIT_FAILURE);

    case 0:
        printf("This version of the CSORT program was written by Jeremy Trendoff - 101160306\n");
        printf("\nWelcome to the CSORT Program!\n");
        printf("Please follow the prompts!\n");

        /* Initialize arrays. */
        char input[8];

        printf("Enter the char array of length 7 to sort (EXAMPLE: ACVbhic) : ");
        fgets(input, 8, stdin);

        shared_stuff->A1 = input[0];
        shared_stuff->A2 = input[1];
        shared_stuff->A3 = input[2];
        shared_stuff->A4 = input[3];
        shared_stuff->A5 = input[4];
        shared_stuff->A6 = input[5];
        shared_stuff->A7 = input[6];

        /* Initialize Semaphores. */
        shared_stuff->A3_semid = create_semaphore((key_t) 1235);
        initialize_semaphore(shared_stuff->A3_semid);

        shared_stuff->A5_semid = create_semaphore((key_t) 1236);
        initialize_semaphore(shared_stuff->A5_semid);

        /* Initialize sorted flag. */
        shared_stuff->sorted = 0;

        printf("\n");

        if (debug_mode)
            printf("Shared Memory Initialized!\n");

        exit(EXIT_SUCCESS);
    }

    waitpid(pid);

    /* Run the processes to sort the array. */

    while (!shared_stuff->sorted)
    {
        pid1 = fork();
        switch (pid1)
        {
        case -1:
            perror("Fork Failed for pid1");
            exit(EXIT_FAILURE);

        case 0:
            if (!shared_stuff->sorted)
            {
                if (debug_mode)
                {
                    printf("Process 1 waiting for semaphore A3.\n");
                }

                if (!acquire_semaphore(shared_stuff->A3_semid))
                    exit(EXIT_FAILURE);

                char segment_1[3] = {shared_stuff->A1, shared_stuff->A2, shared_stuff->A3};

                if (debug_mode)
                {
                    printf("Process 1 has acquired semaphore A3.\n");
                }

                if (!sorted(segment_1, 3))
                {
                    if (debug_mode)
                        printf("Process 1 sorting segment 1.\n");

                    char *new_segment = sort_segment(segment_1);

                    if (debug_mode)
                    {
                        printf("The new sorted segment 1 is:\n");
                        print_char_array(new_segment, 3);
                    }

                    shared_stuff->A1 = new_segment[0];
                    shared_stuff->A2 = new_segment[1];
                    shared_stuff->A3 = new_segment[2];
                } else 
                {
                    if (debug_mode)
                        printf("Process 1 not sorting segment 1. Segment 1 is already sorted.\n");
                }

                if (!release_semaphore(shared_stuff->A3_semid))
                    exit(EXIT_FAILURE);

                if (debug_mode)
                {
                    printf("Process 1 released semaphore A3.\n");
                }
                exit(EXIT_SUCCESS);
            } else {
                exit(EXIT_SUCCESS);
            }
        }

        pid2 = fork();
        switch (pid2)
        {
        case -1:
            perror("Fork Failed for pid2");
            exit(EXIT_FAILURE);

        case 0:
            if (!shared_stuff->sorted)
            {
                if (debug_mode)
                {
                    printf("Process 2 waiting for semaphores A3 and A5.\n");
                }

                if (!acquire_semaphore(shared_stuff->A3_semid)) 
                    exit(EXIT_FAILURE);

                if (debug_mode)
                {
                    printf("Process 2 has acquired semaphore A3.\n");
                }

                if (!acquire_semaphore(shared_stuff->A5_semid)) 
                    exit(EXIT_FAILURE);

                if (debug_mode)
                {
                    printf("Process 2 has acquired semaphore A5.\n");
                }

                char segment_2[3] = {shared_stuff->A3, shared_stuff->A4, shared_stuff->A5};

                if (!sorted(segment_2, 3))
                {
                    if (debug_mode)
                    {
                        printf("Process 2 sorting segment 2.\n");
                    }

                    char *new_segment = sort_segment(segment_2);

                    if (debug_mode)
                    {
                        printf("The new sorted segment 2 is:\n");
                        print_char_array(new_segment, 3);
                    }

                    shared_stuff->A3 = new_segment[0];
                    shared_stuff->A4 = new_segment[1];
                    shared_stuff->A5 = new_segment[2];
                } else 
                {
                    if (debug_mode)
                        printf("Process 2 not sorting segment 2. Segment 2 is already sorted.\n");
                }

                if (!release_semaphore(shared_stuff->A3_semid)) 
                    exit(EXIT_FAILURE);
                if (!release_semaphore(shared_stuff->A5_semid))
                    exit(EXIT_FAILURE);

                if (debug_mode)
                {
                    printf("Process 2 released semaphore A3 and A5.\n");
                }
                exit(EXIT_SUCCESS);
            } else 
            {
                exit(EXIT_SUCCESS);
            }
        }

        pid3 = fork();
        switch (pid3)
        {
        case -1:
            perror("Fork Failed for pid3");
            exit(EXIT_FAILURE);

        case 0:
            if (!shared_stuff->sorted)
            {
                if (debug_mode)
                {
                    printf("Process 3 waiting for semaphore A5.\n");
                }

                if (!acquire_semaphore(shared_stuff->A5_semid))
                    exit(EXIT_FAILURE);

                char segment_3[3] = {shared_stuff->A5, shared_stuff->A6, shared_stuff->A7};

                if (debug_mode)
                {
                    printf("Process 3 has acquired semaphore A5.\n");
                }

                if (!sorted(segment_3, 3))
                {
                    if (debug_mode)
                        printf("Process 3 sorting segment 3.\n");

                    char *new_segment = sort_segment(segment_3);

                    if (debug_mode)
                    {
                        printf("The new sorted segment 3 is:\n");
                        print_char_array(new_segment, 3);
                    }

                    shared_stuff->A5 = new_segment[0];
                    shared_stuff->A6 = new_segment[1];
                    shared_stuff->A7 = new_segment[2];
                } else 
                {
                    if (debug_mode)
                        printf("Process 3 not sorting segment 3. Segment 3 already sorted.\n");
                }

                if (!release_semaphore(shared_stuff->A5_semid))
                    exit(EXIT_FAILURE);

                if (debug_mode)
                {
                    printf("Process 3 released semaphore A5.\n");
                }
                exit(EXIT_SUCCESS);
            } else 
            {
                exit(EXIT_SUCCESS);
            }
        }

        /* Run process to check if the array is sorted. */

        pid4 = fork();
        switch (pid4)
        {
        case -1:
            perror("Fork Failed for pid3");
            exit(EXIT_FAILURE);

        case 0: ;
            char array[7];
            array[0] = shared_stuff->A1;
            array[1] = shared_stuff->A2;
            array[2] = shared_stuff->A3;
            array[3] = shared_stuff->A4;
            array[4] = shared_stuff->A5;
            array[5] = shared_stuff->A6;
            array[6] = shared_stuff->A7;

            if (debug_mode)
            {
                printf("Checking if array is sorted.\n");
            }

            if (sorted(array, 7))
            {
                shared_stuff->sorted = 1;

                if (debug_mode)
                {
                    printf("Array is sorted!\n");
                }

                exit(EXIT_SUCCESS);
            }

            if (debug_mode)
            {
                printf("Array is not sorted.\n");
            }
            
            exit(EXIT_SUCCESS);
        }
    }

    waitpid(pid1);
    waitpid(pid2);
    waitpid(pid3);
    waitpid(pid4);

    /* Ensure output is in lowercase. */
    shared_stuff->A1 = get_char_from_value(assign_value(shared_stuff->A1));
    shared_stuff->A2 = get_char_from_value(assign_value(shared_stuff->A2));
    shared_stuff->A3 = get_char_from_value(assign_value(shared_stuff->A3));
    shared_stuff->A4 = get_char_from_value(assign_value(shared_stuff->A4));
    shared_stuff->A5 = get_char_from_value(assign_value(shared_stuff->A5));
    shared_stuff->A6 = get_char_from_value(assign_value(shared_stuff->A6));
    shared_stuff->A7 = get_char_from_value(assign_value(shared_stuff->A7));

    /* Print the results. */
    if (debug_mode)
        printf("\n");

    printf("The sorted array is:\n");
    print_shared_array(*shared_stuff);

    delete_semaphore(shared_stuff->A3_semid);
    delete_semaphore(shared_stuff->A5_semid);

    /* Deallocate the shared memory */
    shared_stuff = (shared_use_state_t *)shared_memory;
    if (shmdt(shared_memory) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "shmctl(IPC_RMID) failed at the end\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}