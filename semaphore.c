/**
 * @file semaphore.c
 * @author Jeremy Trendoff - 101160306
 * @brief Semaphore operations.
 */

#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

#include "semaphore.h"
#include "semun.h"

/**
 * @brief Create a semaphore object
 * 
 * @param key The key to create the semaphore.
 * @return int The semid.
 */
int create_semaphore(key_t key)
{
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1)
    {
        fprintf(stderr, "semget failed\n");
        exit(EXIT_FAILURE);
    }
    return semid;
}

/**
 * @brief Initialize a semaphore.
 * 
 * @param semid The id of the semaphore.
 */
void initialize_semaphore(int semid)
{
    union semun union_semun;
    union_semun.val = 1;
    if (semctl(semid, 0, SETVAL, union_semun) == -1)
    {
        fprintf(stderr, "Failed to initialize semaphore\n");
    }
}

/**
 * @brief Acquire a semaphore.
 * 
 * @param semid The id of the semaphore.
 */
int acquire_semaphore(int semid)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;

    if (semop(semid, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore wait operation failed\n");
        return 0;
    }

    return 1;
}

/**
 * @brief Get the semaphore value object
 * 
 * @param semid The id of the semaphore.
 */
int get_semaphore_value(int semid)
{
    int semval = semctl(semid, 0, GETVAL, 0);
    if (semval == -1)
    {
        fprintf(stderr, "semaphore check operation failed\n");
        exit(EXIT_FAILURE);
    }
    return semval;
}

/**
 * @brief Release semaphore object.
 * 
 * @param semid The id of the semaphore.
 */
int release_semaphore(int semid)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;

    if (semop(semid, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore release operation failed\n");
        return 0;
    }

    return 1;
}

/**
 * @brief Delete a semaphore.
 * 
 * @param semid The id of the semaphore.
 */
void delete_semaphore(int semid)
{
    union semun del_sem_union;
    if (semctl(semid, 0, IPC_RMID, del_sem_union) == -1)
    {
        fprintf(stderr, "semaphore deletion failed\n");
        exit(EXIT_FAILURE);
    }
}