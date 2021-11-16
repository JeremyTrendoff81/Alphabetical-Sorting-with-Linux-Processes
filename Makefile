CSORT: CSORT.o CharOperations.o semaphore.o 
	gcc -o CSORT CSORT.o CharOperations.o semaphore.o

CSORT.o: CSORT.c semun.h semaphore.h CharOperations.h SharedMem.h
	gcc -c CSORT.c

CharOperations.o: CharOperations.c CharOperations.h
	gcc -c CharOperations.c

semaphore.o: semaphore.c semun.h semaphore.h
	gcc -c semaphore.c 


