#pragma once
#include "cell.h"

#define CELL(_cmd, _signal, _ms) {.cmd=_cmd, .signal=_signal, .ms=_ms},

/*
 * .ms >= 0 : will run every .ms
 * .ms = -1 : will run only on startup
 * .signal = -1 : will not run on signal
 * .signal = <34...64> : will run cell on signal
 */

Cell cells[] = {
	CELL("date", -1, 1000)
};


