/*
 * interrupt_main.c
 *
 *  Created on: Apr 29, 2025
 *      Author: hassa
 */
#include <util/delay.h>
#include "../reg.h"
#include "../../Service/STD_TYPES.h"
#include "../../Service/bit_math.h"
#include "interrupt_header.h"



void GIE_voidEnableGlobleIneterrupt(){
//	SET_BIT(SREG , 7);
	__asm("SEI");
}

void GIE_voidDisnableGlobleIneterrupt(){
//	CLR_BIT(SREG , 7);
	__asm("CLI");

}
