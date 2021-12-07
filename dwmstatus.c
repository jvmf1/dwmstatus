#include <slib/slstr.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include "config.h"
#include "cell.h"

pthread_mutex_t cell_lock;
// status refresh time in ms
#define REFRESH 1000

int lencells= sizeof(cells)/sizeof(Cell);
Cell *signals[31];

Display *display;
Window root;
sl_string *status;

void load_signals() {
	for (int i=0;i<lencells;i++) {
		if (cells[i].signal >= 34 && cells[i].signal <= 64) {
			signals[cells[i].signal-34]=&cells[i];
		}
	}
}

void update_status() {
	pthread_mutex_lock(&cell_lock);
	sl_str_clear(status);	
	for (int i=0;i<lencells;i++) {
		if (sl_str_scat(status, cells[i].data)==-1) return;
	}
	XStoreName(display, root, status->data);
	XSync(display, false);
	pthread_mutex_unlock(&cell_lock);
}

void signal_cell(int signum) {
	if (signum <= 33 || signum >= 65) return;
	int sig = signum-34;
	Cell *c = signals[sig];
	if (c==NULL) return;
	cell_run(c, &cell_lock);
	update_status();
}

int main() {
	if (pthread_mutex_init(&cell_lock, NULL)!=0) return 1;
	status = sl_str_create_cap(100);
	display = XOpenDisplay(NULL);
	root = DefaultRootWindow(display);

	if (status==NULL) return 1;

	// load cells
	for (int i=0;i<lencells;i++) {
		int sucess = cell_load(&cells[i]);
		if (sucess==-1) return 1;
	}

	load_signals();

	// sets signals
	for (int i=34;i<=64;i++) {
		signal(i, signal_cell);
	}

	// run cells
	pthread_t threads[lencells];
	for (int i=0;i<lencells;i++) {
		pthread_create(&threads[i], NULL, cell_start, &cells[i]);
	}


	struct timespec ts;
	ts.tv_sec = REFRESH / 1000;
	ts.tv_nsec = (REFRESH % 1000) * 1000000; 

	while (1) {
		update_status();
		nanosleep(&ts, NULL);
	}
}
