#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 Keyboard.
 */

/*waiting for KBC*/
#define WAIT_KBC 20000 

/**/
#define IRQ1 1
#define IRQ0 0

/*i8042 ports*/

#define STATUS_REGISTER 0x64 //read the KBC state

#define INPUT_BUFFER_COMMANDS 0x64 //write commands to KBC access

#define INPUT_BUFFER_ARGUMENTS 0x60 //write arguments to KBC access

#define OUTPUT_BUFFER 0x60 //read sandcodes bothe make and break ans return values from KBC commands

/*status bits*/

#define OUT_BUFF BIT(0)

#define IN_BUFF BIT(1)

#define SYS_FLAG BIT(2)

#define DATA_CMD BIT(3)

#define KBC_PAR_ERR BIT(7)

#define KBC_TO_ERR BIT(6)

/*Commands*/

#define READ_COMMAND 0x20

#define WRITE_COMMAND 0x60

/*KEYS*/

#define ESCAPE 0x81 //sandcode for ESC

void (double_buffer)();




#endif
