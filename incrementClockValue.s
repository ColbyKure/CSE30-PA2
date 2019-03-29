/*
 * Filename: incrementClockValue.s
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: holds function incrementClockValue
 * Date: May 02 2018
 * Sources of Help: notes, piazza
 */

	.cpu	cortex-a53
	.syntax	unified

	.global	incrementClockValue

	.equ	FP_OFFSET, 4

	.text
	.align	2


/*
 * Function Name: incrementClockValue()
 * Function Prototype: unisgned char incrementClockValue(unsigned char BCDbits,
 * 	const unsigned int maxValue);
 * Description: function will increment the nibble passed into BCDbits mod maxV
 * Parameters: 
 * 	arg 1 - char BCDbits - 4 bits that need to be incremented
 * 	arg 2 - maxValue - maxValue before incrementing back to 0
 * Side Effects: none 
 * Error Conditions: none
 * Return Value: return BCDbits + 1 else return 0 if BCDbits > maxValue
 * 
 * Registers used: 
 * 	r0 - arg 1 
 * 	r1 - arg 2
 * 
 * Local variables: none
 */

incrementClockValue:
	@ prologue 
	push	{fp, lr}
	add	fp, sp, FP_OFFSET

	cmp	r0, r1
	bge	overflow
	
	add	r0, r0, 1		@ increment BCDbits
	b	end

overflow:
	mov	r0, 0			@ set return value to 0

end:
	sub	sp, fp, FP_OFFSET
	pop	{fp, pc}
