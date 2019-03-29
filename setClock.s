/*
 * Filename: setClock.s
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: file for function setClock()
 * Date: May 02 2018
 * Sources of Help: notes, piazza
 */

	.cpu	cortex-a53	@ version of pi
	.syntax	unified		@ modern ARM syntax

	.global	setClock	@ setClock is global function
	
	.equ	FP_OFFSET, 4
	.equ	LOCAL_SPACE, 8
	.equ	PARAM_SPACE, 8
	.equ	UPPER_OFF, -8
	.equ	LOWER_OFF, -12
	.equ	CLOCK_OFF, -16
	.equ	T_INFO_OFF, -20
	.equ	BASE, 10
	.equ	SHIFT_FOUR, 4
	.equ	CLOCK_H, 0
	.equ	CLOCK_M, 1
	.equ	CLOCK_S, 2
	.equ	CLOCK_AMPM, 3

	.text			@ start instruction segment
	.align	2		@ align to 2^2 = 4 offset


/*
 * Function Name: setClock()
 * Function Prototype: void setClock(unsigned char clock[], const struct 
 * 	tinfo * tmPtr);
 * Description: using the info in tmPtr set time in clock[]
 * Parameters: 
 * 	arg 1 - char clock[] - char array for BCD clock
 * 	arg 2 - struct tInfo * tmPtrf - struct with time info
 * Side Effects: none 
 * Error Conditions: none
 * Return Value: none
 * 
 * Registers used: 
 * 	r0 - arg 1 - clock - return value - 
 * 	r1 - arg 2 - struct with time info
 * 	r2 - local 1 - upper
 * 	r3 - local 2 - lower - holder for BASE
 * 
 * Local variables: TODO
 * 	<name> - <fp offset> -- <description>
 */

setClock:
	@ Prologue
	push	{fp, lr}
	add	fp, sp,  FP_OFFSET
	
	@ save local
	sub	sp, sp, LOCAL_SPACE
	mov	r2, 0
	str	r2, [fp, UPPER_OFF]
	mov	r3, 0
	str	r3, [fp, LOWER_OFF]

	@ save parameters 
	sub	sp, sp, PARAM_SPACE
	str	r0, [fp, CLOCK_OFF]
	str	r1, [fp, T_INFO_OFF]

	@ extract integer for seconds
	ldr	r3, =tInfo_secOffset		@ load mem address 
	ldr	r3, [r3]			@ get value of secOffset

	ldr	r1, [fp, T_INFO_OFF]		@ load tInfo *
	ldr	r0, [r1, r3]			@ load tmPtr->tm_sec

	mov	r3, BASE
	udiv	r2, r0, r3			@ upper = sec/10
	str	r2, [fp, UPPER_OFF]

	mov	r1, BASE			@ mov 10 into param 2 slot
	bl	myRemainder

	str	r0, [fp, LOWER_OFF]		@ lower = sec%10

	ldr	r2, [fp, UPPER_OFF]		@ load upper
	lsl	r2, r2, SHIFT_FOUR		@ Shift left 4 bits

	add	r2, r2, r0			@ upper = upper + lower
	ldr	r0, [fp, CLOCK_OFF]		@ load clock[]
	strb	r2, [r0, CLOCK_S]

	@ extract minutes
	ldr	r3, =tInfo_minOffset
	ldr	r3, [r3]			@ load min offset value

	ldr	r1, [fp, T_INFO_OFF]		@ load tInfo *
	ldr	r0, [r1, r3]			@ load tmPtr->tm_min

	mov	r3, BASE
	udiv	r2, r0, r3			@ upper = min/10
	str	r2, [fp, UPPER_OFF]

	mov	r1, BASE			@ mov 10 into param 2 slot
	bl	myRemainder

	str	r0, [fp, LOWER_OFF]		@ lower = min%10

	ldr	r2, [fp, UPPER_OFF]		@ load upper
	lsl	r2, r2, SHIFT_FOUR		@ Shift left 4 bits

	add	r2, r2, r0			@ upper = upper + lower
	ldr	r0, [fp, CLOCK_OFF]		@ load clock[]
	strb	r2, [r0, CLOCK_M]

	@ extract hour
	ldr	r3, =tInfo_hourOffset
	ldr	r3, [r3]			@ load hour offset value

	ldr	r1, [fp, T_INFO_OFF]		@ load tInfo *
	ldr	r0, [r1, r3]			@ load tmPtr->tm_hour

	mov	r3, BASE
	udiv	r2, r0, r3			@ upper = hour/10
	str	r2, [fp, UPPER_OFF]

	mov	r1, BASE			@ mov 10 into param 2 slot
	bl	myRemainder

	str	r0, [fp, LOWER_OFF]		@ lower = hour%10

	ldr	r2, [fp, UPPER_OFF]		@ load upper
	lsl	r2, r2, SHIFT_FOUR		@ Shift left 4 bits

	add	r2, r2, r0			@ upper = upper + lower
	ldr	r0, [fp, CLOCK_OFF]		@ load clock[]
	strb	r2, [r0, CLOCK_H]

	@ extract am/pm
	ldr	r3, =tInfo_ampmOffset
	ldr	r3, [r3]			@ load a or p

	ldr	r1, [fp, T_INFO_OFF]		@ load tInfo *
	ldr	r2, [r1, r3]			@ load tmPtr->tm_ampm

	ldr	r0, [fp, CLOCK_OFF]		@ load clock

	str	r2, [r0, CLOCK_AMPM]		@ set clock[3] to ampm
	@ Epilogue
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
