#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 keyboard and mouse.
 */


/// <summary>
/// waiting for the keyboard/mouse buffer to fill in the int handler
/// </summary>
#define WAIT_KBC 20000 

/**/
/// <summary>
/// IRQ Line for the keyboard
/// </summary>
#define IRQ1 1
/// <summary>
/// IRQ Line for the timer
/// </summary>
#define IRQ0 0
/// <summary>
/// IRQ Line for the mouse
/// </summary>
#define IRQ12 12

/*i8042 ports*/

/// <summary>
/// register from which you read the status of the keyboard
/// </summary>
#define STATUS_REGISTER 0x64 //read the KBC state

/// <summary>
/// register to which input buffer commands are written
/// </summary>
#define INPUT_BUFFER_COMMANDS 0x64 //write commands to KBC access

/// <summary>
/// register to which input buffer arguments are written
/// </summary>
#define INPUT_BUFFER_ARGUMENTS 0x60 //write arguments to KBC access

/// <summary>
/// register of the output buffer from where you read scancodes
/// </summary>
#define OUTPUT_BUFFER 0x60 //read scancodes bothe make and break and return values from KBC commands

/*status bits */

/// <summary>
/// flag for when output buffer is empty are ready to be read from
/// </summary>
#define OUT_BUFF BIT(0)

/// <summary>
/// flag for when the input buffer is empty and we are ready to write to it
/// </summary>
#define IN_BUFF BIT(1)

/// <summary>
/// system flag
/// </summary>
#define SYS_FLAG BIT(2)

/// <summary>
/// waiting for the keyboard
/// </summary>
#define DATA_CMD BIT(3)

/// <summary>
/// output buffer's data is coming from the mouse 
/// </summary>
#define AUX_BIT BIT(5)

/// <summary>
/// parity error flag
/// </summary>
#define KBC_PAR_ERR BIT(7)

/// <summary>
/// timeout error flag
/// </summary>
#define KBC_TO_ERR BIT(6)

/*Commands*/

/// <summary>
/// command to read 
/// </summary>
#define READ_COMMAND 0x20

/// <summary>
/// command to write
/// </summary>
#define WRITE_COMMAND 0x60

/// <summary>
/// command to issue to the mouse buffer to let it know it is about to receive a command
/// </summary>
#define ISSUE_COMMAND_TO_THE_MOUSE 0xD4

/*ARGUMENTS MOUSE*/


/// <summary>
/// enable mouse argument
/// </summary>
#define ENABLE_MOUSE_DATA 0xF4

/// <summary>
/// disable mouse argument
/// </summary>
#define DISABLE_MOUSE_DATA 0xF5

/// <summary>
/// set stream mouse argument
/// </summary>
#define SET_STREAM_MODE 0xEA

/// <summary>
/// set remote mouse argument
/// </summary>
#define SET_REMOTE_MODE 0xF0

/// <summary>
/// read data mouse argument
/// </summary>
#define READ_DATA_MOUSE 0xEB

/// <summary>
/// reset mouse argument
/// </summary>
#define RESET_MOUSE 0xFF

/*KEYS*/

/// <summary>
/// scancode for the escape key
/// </summary>
#define ESCAPE 0x81 //sandcode for ESC

/// <summary>
/// scancode for the w key
/// </summary>
#define W_KEY 0x11 //sandcode for w

/// <summary>
/// scancode for the s key
/// </summary>
#define S_KEY  0x1f //sandcode for ESC

/*AKNOWLEDGMENTS*/

/// <summary>
/// aknowledgment recieved when the issue_command_to_mouse command is wrong
/// </summary>
#define INVALID_BYTE 0xFE

/// <summary>
/// aknowledgment recieved when the issue_command_to_mouse command results in an error
/// </summary>
#define IS_ERROR 0xFC

/// <summary>
/// aknowledgment recieved when the issue_command_to_mouse command is successfull
/// </summary>
#define IS_OK 0xFA


#endif
