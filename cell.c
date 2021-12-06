#include <slstr.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include "cell.h"

void* cell_start(void *arg) {
	Cell *c = arg;
	if (c->ms >= 0) {
		while (1) {
			cell_run(c, &cell_lock);
			cell_sleep(c);
		}
	}
	cell_run(c, &cell_lock);
	return NULL;
}

int cell_load(Cell *c) {
	sl_string *data = sl_str_create_cap(20);
	if (data==NULL) {
		return -1;
	}
	c->data=data;
	return 0;
}

void cell_sleep(Cell *c) {
	struct timespec ts;
	ts.tv_sec = c->ms / 1000;
	ts.tv_nsec = (c->ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void cell_run(Cell *c, pthread_mutex_t *lock) {
	FILE *pf = popen(c->cmd, "r");
	if (pf==NULL) return;
	pthread_mutex_lock(lock);
	sl_str_clear(c->data);
	sl_str_fgets(c->data, pf, 20);
	sl_str_replace_char(c->data, '\n', ' ');
	if (c->data->data[c->data->len-1]==' ') sl_str_replace_charn(c->data, c->data->len-1, '\0');
	pthread_mutex_unlock(lock);
	fclose(pf);
}
