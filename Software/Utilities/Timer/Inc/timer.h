/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
AT91 Port: Peter CHRISTEN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __TIMERSCFG_H__
#define __TIMERSCFG_H__

#include "config.h"
#include "BSP_timer.h"
#include "type.h"
// Whatever your microcontroller, the timer wont work if
// TIMEVAL is not at least on 32 bits

// The timer of the AT91 counts from 0000 to 0xFFFF
#define TIMEVAL_MAX 0xFFFF
#define MAX_NB_TIMER 40



/* --------- types and constants definitions --------- */
#define TIMER_FREE 0
#define TIMER_ARMED 1
#define TIMER_TRIG 2
#define TIMER_TRIG_PERIOD 3

#define TIMER_NONE -1
 
#define TIMER_HANDLE INT16

typedef void (*TimerCallback_t)(UNS32 data);

struct struct_s_timer_entry {
	UNS8 state;
	UNS32 data;
	TimerCallback_t callback; /* The callback func. */
	TIMEVAL val;
	TIMEVAL interval; /* Periodicity */
};

typedef struct struct_s_timer_entry s_timer_entry;

#define M_TO_TIMEVAL(s)		((s)*60*1000*10)
#define S_TO_TIMEVAL(s)		((s)*1000*10)	
#define MS_TO_TIMEVAL(ms) ((ms)*10)
#define US_TO_TIMEVAL(us) ((us)/100)

void TimeDispatch(void);
TIMER_HANDLE SetAlarm(UNS32 data, TimerCallback_t callback, TIMEVAL value, TIMEVAL period);
TIMER_HANDLE DelAlarm(TIMER_HANDLE handle);
TIMER_HANDLE ResetAlarm(TIMER_HANDLE handle);
#endif
