#ifndef _LCOM_I8254_H_
#define _LCOM_I8254_H_

#include <lcom/lcf.h>

/** @defgroup i8254 i8254
 * @{
 *
 * Constants for programming the i8254 Timer
 */

/// <summary>
/// frequency of the timer clock
/// </summary>
#define TIMER_FREQ 1193182 
/// <summary>
/// IRQ line for timer
/// </summary>
#define TIMER0_IRQ 0
/// <summary>
/// IRQ line for keyboard
/// </summary>
#define IRQ1 1
/* I/O port addresses */

/// <summary>
/// count register for Timer 0
/// </summary>
#define TIMER_0    0x40 
/// <summary>
/// count register for Timer 1
/// </summary>
#define TIMER_1    0x41 
/// <summary>
/// count register for Timer 2
/// </summary>
#define TIMER_2    0x42 
/// <summary>
/// control register for timers
/// </summary>
#define TIMER_CTRL 0x43 


/* Timer control */

/* Timer selection: bits 7 and 6 */

/// <summary>
/// Control word to select timer 0
/// </summary>
#define TIMER_SEL0   0x00   
/// <summary>
/// Control word to select timer 1
/// </summary>           
#define TIMER_SEL1   BIT(6)   
/// <summary>
/// Control word to select timer 2
/// </summary>         
#define TIMER_SEL2   BIT(7)          
/// <summary>
///Read Back Command
/// </summary> 
#define TIMER_RB_CMD (BIT(7) | BIT(6)) 

/* Register selection: bits 5 and 4 */

/// <summary>
/// Initialize the least significative bit of the counter
/// </summary> 
#define TIMER_LSB     BIT(4)        
/// <summary>
/// Initialize the most significative bit of the counter
/// </summary>           
#define TIMER_MSB     BIT(5)              
/// <summary>
/// Initialize the most and the least significative bits of the counter
/// </summary> 
#define TIMER_LSB_MSB (TIMER_LSB | TIMER_MSB) 

/* Operating mode: bits 3, 2 and 1 */

/// <summary>
/// Use modo 3: square wave generator
/// </summary> 
#define TIMER_SQR_WAVE (BIT(2) | BIT(1)) 
/// <summary>
/// Use modo 2: Rate generator
/// </summary>
#define TIMER_RATE_GEN BIT(2)           

/* Counting mode: bit 0 */
/// <summary>
/// BCD counter
/// </summary>
#define TIMER_BCD 0x01 
/// <summary>
/// binary counter
/// </summary>
#define TIMER_BIN 0x00 

/* READ-BACK COMMAND FORMAT */

/// <summary>
/// Used to format a read-back command: specifies that we want to read the count
/// </summary>
#define TIMER_RB_COUNT_  BIT(5)
/// <summary>
/// Used to  format read-back command: specifies that we want to read the status
/// </summary>
#define TIMER_RB_STATUS_ BIT(4)
/// <summary>
/// Used to  format read-back command: specifies which timer we wish to know the configuration of 
/// </summary>
#define TIMER_RB_SEL(n)  BIT((n) + 1)

/**@}*/

#endif /* _LCOM_I8254_H */
