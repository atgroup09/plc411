/*
 * Copyright Nucleron R&D LLC 2016
 *
 * This file is licensed under the terms of YAPL,
 * see License.txt for details.
 */

#ifndef _PLC_TICK_H_
#define _PLC_TICK_H_

#include <stdint.h>


void plc_tick_setup(uint64_t tick_next, uint64_t tick_period);


#endif /* _PLC_TICK_H_ */
