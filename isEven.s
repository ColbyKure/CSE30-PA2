/* 
 * File: isEven.s
 * Author: Colby Kure 
 * Userid: cs30xdc
 * Description: This function will check if the parameter is even
 * Date: 4/17/18
 * Sources of help: notes
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of pis 
	.syntax	unified		@ modern ARM syntax

	.equ	FP_OFFSET, 4	@ set fp to base of saved registers
	.equ	EVEN, 2

	.global	isEven		@ isInRnage is global function

	.text			@ start text section 
	.align	2		@ align at 4 offset 

/*
 * Function name: isEven()
 * Prototype: isEven(long value)
 * Description: Checks if value is even
 * Paramters: 	value - the value to check
 * Side Effects: None
 * Error Condition: None
 * Return Value: 0 for not even and 1 for even
 *
 * Registers used:
 *	
 *	r0 - arg 1 - value 
 */

isEven:
	@ Standard Prologue
	push	{fp, lr}		@ save registers fp anf lr on stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of sved registers 

	mov	r1, EVEN		@ move 2 into r1
	bl	myRemainder		@ call long myRemainder(dvded, dvsr)
	
	cmp	r0, 0
	bne	odd

	mov	r0, 1
	b	return

odd:
	mov	r0, 0

return:
	@ Standard Epilogue
	sub	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp and lr into pc
