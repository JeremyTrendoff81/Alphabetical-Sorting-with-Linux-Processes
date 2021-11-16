/**
 * @file semaphore.h
 * @author Jeremy Trendoff - 101160306
 * @brief A Header file for semaphore operations.
 */
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/sem.h>

/**
 * @brief Create a semaphore object
 * 
 * @param key The key to create the semaphore.
 * @return int The semid.
 */
int create_semaphore(key_t key);

/**
 * @brief Initialize a semaphore.
 * 
 * @param semid The id of the semaphore.
 */
void initialize_semaphore(int semid);

/**
 * @brief Acquire a semaphore.
 * 
 * @param semid The id of the semaphore.
 */
int acquire_semaphore(int semid);

/**
 * @brief Get the semaphore value object
 * 
 * @param semid The id of the semaphore.
 */
int get_semaphore_value(int semid);

/**
 * @brief Release semaphore object.
 * 
 * @param semid The id of the semaphore.
 */
int release_semaphore(int semid);

/**
 * @brief Delete a semaphore.
 * 
 * @param semid The id of the semaphore.
 */
void delete_semaphore(int semid);

#endif