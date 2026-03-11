/*
 * bit_math.h
 *
 *  Created on: 11 Apr 2025
 *      Author: AMIT
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT_NO)  REG |= (1<<BIT_NO)
#define TOG_BIT(REG,BIT_NO)  REG ^= (1<<BIT_NO)
#define CLR_BIT(REG,BIT_NO)  REG &=~(1<<BIT_NO)
#define GET_BIT(REG,BIT_NO)  (REG>>BIT_NO) & 1
/*
#define ASS_BIT(REG,BIT_NO,VAL)
@todo
macro rotate right
macro rotate left
set half byte
CLR half byte
assign bit
*/

#endif /* BIT_MATH_H_ */
