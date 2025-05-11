#ifndef		BITMATH_H
#define 	BITMATH_H

#define SETBIT(REG, PIN)				REG |=(1<<PIN)
#define CLRBIT(REG, PIN)				REG &=~(1<<PIN)
#define TOGBIT(REG, PIN)				REG ^=(1<<PIN)
#define GETBIT(REG, PIN)				((REG>>PIN)&1)


#endif
