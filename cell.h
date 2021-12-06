#pragma once
#include <pthread.h>

typedef struct Cell {
	char *cmd;
	int ms;
	int signal;
	sl_string *data;
} Cell;

extern pthread_mutex_t cell_lock;

int cell_load(Cell *c);
void cell_sleep(Cell *c);
void cell_run(Cell *c, pthread_mutex_t *lock);
void* cell_start(void *arg);
