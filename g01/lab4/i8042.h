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
#define IRQ12 12

/*i8042 ports*/

#define STATUS_REGISTER 0x64 //read the KBC state

#define INPUT_BUFFER_COMMANDS 0x64 //write commands to KBC access

#define INPUT_BUFFER_ARGUMENTS 0x60 //write arguments to KBC access

#define OUTPUT_BUFFER 0x60 //read sandcodes bothe make and break ans return values from KBC commands

/*status bits */

#define OUT_BUFF BIT(0)

#define IN_BUFF BIT(1)

#define SYS_FLAG BIT(2)

#define DATA_CMD BIT(3)

#define AUX_BIT BIT(5)

#define KBC_PAR_ERR BIT(7)

#define KBC_TO_ERR BIT(6)

/*Commands*/

#define READ_COMMAND 0x20

#define WRITE_COMMAND 0x60

#define ISSUE_COMMAND_TO_THE_MOUSE 0xD4

/*ARGUMENTS MOUSE*/

#define ENABLE_MOUSE_DATA 0xF4

#define DISABLE_MOUSE_DATA 0xF5

#define SET_STREAM_MODE 0xEA

#define SET_REMOTE_MODE 0xF0

#define READ_DATA_MOUSE 0xEB

#define RESET_MOUSE 0xFF

/*KEYS*/

#define ESCAPE 0x81 //sandcode for ESC

/*AKNOWLEDGMENTS*/

#define INVALID_BYTE 0xFE

#define IS_ERROR 0xFC

#define IS_OK 0xFA


#endif
