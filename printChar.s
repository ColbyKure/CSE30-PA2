/* 
 * File: printChar.s
 * Author: Colby Kure 
 * Userid: cs30xdc
 * Description: this will print a char 
 * Date: 4/17/18
 * Sources of help: notes
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of pis 
	.syntax	unified		@ modern ARM syntax

	.equ	FP_OFFSET, 4	@ set fp to base of saved registers

	.section	.rodata

fmt:	.asciz		"%c"

	.global	printChar	@ isInRnage is global function

	.text			@ start text section 
	.align	2		@ align at 4 offset 

/*
 * Function name: printChar()
 * Prototype: void printChar(char ch)
 * Description: prints char to stdout
 * Paramters: 	ch - char to print
 * Side Effects: prints char 
 * Error Condition: None
 * Return Value: None
 *
 * Registers used:
 *	
 *	r0 - arg 1 - ch 
 */

printChar:
	@ Standard Prologue
	push	{fp, lr}		@ save registers fp anf lr on stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of sved registers 

	mov	r1, r0			@ move ch to second paramter
	ldr	r0, =fmt		@ load fmt string into r0
	bl	printf			@ call printf

	@ Standard Epilogue
	sub	sp, fp, FP_OFFSET	@ set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp and lr into pc
