/*
 * Filename: convertTime.s
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Holds the function convertTime
 * Date: May 03 2018
 * Sources of Help: notes and piazza 
 */

	.cpu	cortex-a53
	.syntax	unified

	.global	convertTime

	.equ	FP_OFFSET, 4
	.equ	PARAM_SPACE, 8
	.equ	T_INFO_OFF, -8
	.equ	TM_OFF, -16
	.equ	MAX_HR, 12
	.equ	PM_CHAR, 'P'
	.equ	AM_CHAR, 'A'

	.text
	.align 2

/*
 * Function Name: convertTime()
 * Function Prototype: void convertTime(struct tInfo * ourTime, const struct
 * 	tm * tmPtr);
 * Description: This function will use the tm struct populate the struct pointed
 * 	to by the other struct. tm struct to populate tInfo struct.	
 * Parameters:
 * 	struct tInfo * ourTime - struct to populate
 * 	struct tm * tmPtr - struct with data to use to populate ourTime
 * Side Effects: none 
 * Error Conditions: none 
 * Return Value: none 
 * 
 * Registers used: 
 * 	r0 - arg 1 - tInfoPtr
 * 	r1 - arg 2 - tmPtr 
 * 	r2 - 
 * 	r3 - used to hold the offset values when loading from memory
 * 
 * Local variables: none
 *
 */

convertTime:
	@ prologue
	push	{fp, lr}
	sub	fp, sp, FP_OFFSET

	@ save parameters 
	sub	sp, sp, PARAM_SPACE
	str	r0, [fp, T_INFO_OFF]
	str	r1, [fp, TM_OFF]
	@ get tmPtr->tm_hour 
	ldr	r3, =tm_hour_offset		
	ldr	r3, [r3]
	ldr	r1, [fp, TM_OFF]
	ldr	r0, [r1, r3]			@ r0 holds tmPtr->tm_hour
	cmp	r0, MAX_HR
	blt	am

	@ must be PM
	sub	r0, r0, MAX_HR
	cmp	r0, 0
	bne	non_zero_pm			@ branch if hour is non-zero
	mov	r0, MAX_HR			@ make hour = 0 --> hour = 12
non_zero_pm:
	ldr	r3, =tInfo_hourOffset
	ldr	r3, [r3]
	ldr	r1, [fp, T_INFO_OFF]
	str	r0, [r1, r3]			@ set hour in tInfo
	ldr	r3, =tInfo_ampmOffset
	ldr	r3, [r3]
	mov	r0, PM_CHAR
	str	r0, [r1, r3]			@ set PM 
	b	end_hour

am:
	@ must be AM
	cmp	r0, 0
	bne	non_zero_am			@ branch if hour is non-zero
	mov	r0, MAX_HR			@ make hour = 0 --> hour = 12
non_zero_am:
	ldr	r3, =tInfo_hourOffset
	ldr	r3, [r3]
	ldr	r1, [fp, T_INFO_OFF]
	str	r0, [r1, r3]			@ set hour in tInfo
	ldr	r3, =tInfo_ampmOffset
	ldr	r3, [r3]
	mov	r0, AM_CHAR
	str	r0, [r1, r3]			@ set AM
end_hour:

	@ get tmPtr->tm_min
	ldr	r3, =tm_min_offset		
	ldr	r3, [r3]
	ldr	r1, [fp, TM_OFF]
	ldr	r0, [r1, r3]			@ r0 holds tmPtr->tm_min
	
	ldr	r3, =tInfo_minOffset
	ldr	r3, [r3]
	ldr	r1, [fp, T_INFO_OFF]
	str	r0, [r1, r3]			@ set min in tInfo

	@ get tmPtr->tm_sec
	ldr	r3, =tm_sec_offset		
	ldr	r3, [r3]
	ldr	r1, [fp, TM_OFF]
	ldr	r0, [r1, r3]			@ r0 holds tmPtr->tm_sec
	
	ldr	r3, =tInfo_secOffset
	ldr	r3, [r3]
	ldr	r1, [fp, T_INFO_OFF]
	str	r0, [r1, r3]			@ set sec in tInfo
	
	@ epilogue
	add	sp, fp, FP_OFFSET
	pop	{fp, pc}
