/**
 * @file semun.h
 * @author Jeremy Trendoff - 101160306
 */

#ifndef SEMUN_H
#define SEMUN_H

typedef union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

#endif
