/* 
 * File: myRemainder.s
 * Author: Colby Kure 
 * Userid: cs30xdc
 * Description: This function get remainder in divison
 * Date: 4/17/18
 * Sources of help: notes
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of pis 
	.syntax	unified		@ modern ARM syntax

	.equ	FP_OFFSET, 4	@ set fp to base of saved registers

	.global	myRemainder	@ myRemainder is global function

	.text			@ start text section 
	.align	2		@ align at 4 offset 

/*
 * Function name: myReaminder()
 * Prototype: myRemainder(long dividend, long divisor)
 * Description: Checks for remainder in division 
 * Paramters: 	dividend - number to divide
 *		divisor - number to divide by
 * Side Effects: None
 * Error Condition: divisor is 0 return -1
 * Return Value: -1 on error otherwise reurn remainder
 *
 * Registers used:
 *	
 *	r0 - arg 1 - dividend
 *	r1 - arg 2 - divisor
 *	r2 - local var - quotient
 */

myRemainder:
	@ Standard Prologue
	push	{fp, lr}		@ save registers fp anf lr on stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of sved registers 

	cmp	r1, 0			@ sompare divisor and 0 
	beq	error

	sdiv	r2, r0, r1		@ quotient = dividend / divisor
	mul	r3, r2, r1		@ small = quotient * divisor
	sub	r0, r0, r3		@ return = dividend - small
	b	return			@ branch to return

error:
	mov	r0, -1			@ set return val to -1

return:
	@ Standard Epilogue
	sub	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp and lr into pc
