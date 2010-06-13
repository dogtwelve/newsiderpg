/*
* ============================================================================
*  Name     : Update
*  Part of  : Game
*  Created  : 2005-09-08 by Lu Yan(gameloft beijing)
*  modified : 2005-09-13 by Lu Yan(gameloft beijing)
*  Description:
*     Update screen buffer to LCD screen (in place of system interface IDisplay_UpdateEx).
*    Note that it ONLY supports device LG6000!
*  Version  :
*  Copyright: GameWG S.A.
* ============================================================================
*/

#if defined(__thumb)
#pragma O0
//#define USE_COLOR_664
#define FAST_UPDATE

#define TITLE_HEIGHT		14

#define SCREEN_WIDTH		120
#define SCREEN_HEIGHT		146

//using thumb instruction set

//NOTE: Don`t optimize the code below while compiling this file!

void UpdateEx (unsigned short *pBuf)
{
	unsigned short *pEnd = pBuf + SCREEN_HEIGHT * SCREEN_WIDTH;
	int x1 = 0x800;
	int y1 = TITLE_HEIGHT + 0xa00;
	int x2 = SCREEN_WIDTH - 1 + 0x900;
	int y2 = TITLE_HEIGHT + SCREEN_HEIGHT - 1 + 0xb00;
	int x3 = 0x600;
	int y3 = TITLE_HEIGHT + 0x700;

	__asm
	{
		mov   r7,  0x1C000060

		mov   r1,  #0x510					//0x510
		strh  r1,  [R7,#0x18]
		mov   r1,  x1						//x1 + 0x800
		strh  r1,  [R7,#0x18]
		mov   r1,  y1						//y1 + 0xa00
		strh  r1,  [R7,#0x18]
		mov   r1,  x2						//x2 + 0x900
		strh  r1,  [R7,#0x18]
		mov   r1,  y2						//y2 + 0xb00
		strh  r1,  [R7,#0x18]
		mov   r1,  x3						//x1 + 0x600
		strh  r1,  [R7,#0x18]
		mov   r1,  y3						//y1 + 0x700
		strh  r1,  [R7,#0x18]


		mov   r7,  0x1C0000E0
		mov   r6,  pBuf
		mov   r12, pEnd

		mov   r3,  #0
		mov   r4,  #27

LOOP:
#ifdef  USE_COLOR_664
		ldmia r6!, {r0-r5}					//;load 12 pixels

		strh  r0,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
		lsr   r0,  r0,  #16
		strh  r0,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		strh  r1,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
		lsr   r1,  r1,  #16
		strh  r1,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		strh  r2,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
		lsr   r2,  r2,  #16
		strh  r2,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		strh  r3,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
		lsr   r3,  r3,  #16
		strh  r3,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		strh  r4,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
		lsr   r4,  r4,  #16
		strh  r4,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		strh  r5,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
		lsr   r5,  r5,  #16
		strh  r5,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
#else	//convert 565 to 664
	#ifdef  FAST_UPDATE
		ldmia r6!, {r0, r1}					//;load 4 pixels

		lsl   r2,  r0,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r0,  r2
		strh  r2,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		ror   r0,  r4
		lsl   r2,  r0,  #11
		lsr   r0,  r0,  #22
		orr   r2,  r0
		strh  r2,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		lsl   r2,  r1,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r1,  r2
		strh  r2,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]

		ror   r1,  r4
		lsl   r2,  r1,  #11
		lsr   r1,  r1,  #22
		orr   r2,  r1
		strh  r2,  [r7, #0x1A]
		strh  r7,  [r7, #0x1A]
	#else	//convert 565 to 666
		ldmia r6!, {r0, r1}					//;load 4 pixels

		lsl   r2,  r0,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r0,  r2
		strh  r2,  [r7, #0x1A]
		lsl   r2,  r0,  #31
		lsr   r2,  r2,  #30
		strh  r2,  [r7, #0x1A]

		ror   r0,  r4
		lsl   r2,  r0,  #11
		lsr   r5,  r0,  #22
		orr   r2,  r5
		strh  r2,  [r7, #0x1A]
		lsl   r0,  r0,  #10
		lsr   r0,  r0,  #30
		strh  r0,  [r7, #0x1A]


		lsl   r2,  r1,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r1,  r2
		strh  r2,  [r7, #0x1A]
		lsl   r2,  r1,  #31
		lsr   r2,  r2,  #30
		strh  r2,  [r7, #0x1A]

		ror   r1,  r4
		lsl   r2,  r1,  #11
		lsr   r5,  r1,  #22
		orr   r2,  r5
		strh  r2,  [r7, #0x1A]
		lsl   r1,  r1,  #10
		lsr   r1,  r1,  #30
		strh  r1,  [r7, #0x1A]
	#endif
#endif

		cmp   r6,  r12
		blo   LOOP
	}
}

void UpdateEx (unsigned short *pBuf, int x1, int y1, int w, int h)
{
	unsigned short *pStart = pBuf + y1 * SCREEN_WIDTH + x1 + w;
	unsigned short *pEnd = pStart + h * SCREEN_WIDTH;
	int d2 = SCREEN_WIDTH * 2;
	y1 += TITLE_HEIGHT;
	int x2 = x1 + w - 1 + 0x900;
	int y2 = y1 + h - 1 + 0xb00;
	int x3 = x1 + 0x600;
	int y3 = y1 + 0x700;
	x1 += 0x800;
	y1 += 0xa00;
	w = -w * 2;

	__asm
	{
		mov   h,   lr
		mov   r7,  0x1C000060

		mov   r1,  #0x510					//0x510
		strh  r1,  [R7,#0x18]
		mov   r1,  x1						//x1 + 0x800
		strh  r1,  [R7,#0x18]
		mov   r1,  y1						//y1 + 0xa00
		strh  r1,  [R7,#0x18]
		mov   r1,  x2						//x2 + 0x900
		strh  r1,  [R7,#0x18]
		mov   r1,  y2						//y2 + 0xb00
		strh  r1,  [R7,#0x18]
		mov   r1,  x3						//x1 + 0x600
		strh  r1,  [R7,#0x18]
		mov   r1,  y3						//y1 + 0x700
		strh  r1,  [R7,#0x18]


		mov   r7,  0x1C0000E0

		mov   r3,  #0
		mov   r4,  #27
		mov   r5,  pEnd
		mov   r6,  pStart
		mov   r12, d2
		mov   lr,  w
		mov   r0,  lr

LOOP:
#ifdef  USE_COLOR_664
		ldr   r1,  [r6, r0]					//;load 2 pixels

		strh  r1,  [r7, #0x1A]
		strh  r3,  [r7, #0x1A]

		lsr   r1,  r1,  #16

		strh  r1,  [r7, #0x1A]
		strh  r3,  [r7, #0x1A]
#else	//convert 565 to 664
	#ifdef  FAST_UPDATE
		ldr   r1,  [r6, r0]					//;load 2 pixels

		lsl   r2,  r1,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r1,  r2
		strh  r2,  [r7, #0x1A]
		strh  r3,  [r7, #0x1A]

		ror   r1,  r4
		lsl   r2,  r1,  #11
		lsr   r1,  r1,  #22
		orr   r2,  r1
		strh  r2,  [r7, #0x1A]
		strh  r3,  [r7, #0x1A]
	#else	//convert 565 to 666
		ldr   r1,  [r6, r0]					//;load 2 pixels

		lsl   r2,  r1,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r1,  r2
		strh  r2,  [r7, #0x1A]
		lsl   r2,  r1,  #31
		lsr   r2,  r2,  #30
		strh  r2,  [r7, #0x1A]

		lsr   r1,  r1,  #16

		lsl   r2,  r1,  #21					//;last 11 bits
		lsr   r2,  r2,  #22
		adc   r2,  r3
		sub   r2,  r1,  r2
		strh  r2,  [r7, #0x1A]
		lsl   r2,  r1,  #31
		lsr   r2,  r2,  #30
		strh  r2,  [r7, #0x1A]

//		lsl   r2,  r1,  #5
//		add   r2,  #32
//		lsr   r2,  r2,  #6
//		sub   r2,  r1,  r2
//		ror   r2,  r4			//16
//		strh  r2,  [r7, #0x1A]
//		lsl   r2,  r1,  #15
//		lsr   r2,  r2,  #30
//		strh  r2,  [r7, #0x1A]
	#endif
#endif

		add   r0,  #4
		bmi   LOOP

		add   r6,  r12
		mov   r0,  lr
		cmp   r6,  r5
		blo   LOOP

		mov   lr,  h
	}
}

#endif	//#if defined(__thumb)




