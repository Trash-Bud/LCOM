#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>

/// <summary>
/// Subscribes mouse interrupts
/// </summary>
/// <returns> 0 if it succeds, 1 otherwise </returns>
int(kbc_subscribe)();

/// <summary>
/// Unsubscribes mouse interupts
/// </summary>
/// <returns> 0 if it succeds, 1 otherwise </returns>
int(kbc_unsubscribe)();

/// <summary>
/// Mouse interrupt handler, reads scancodes
/// </summary>
/// <returns></returns>
void(mouse_ih)();

/// <summary>
/// Assembles the mouse packet
/// </summary>
/// <returns></returns>
void (assemble_mouse_packet)();

/// <summary>
/// Writes an argument to the moude
/// </summary>
/// <param name="argument"></param> argument to write
/// <returns></returns>
int(write_argument_to_mouse)(uint8_t argument);

/// <summary>
/// Enables mouse data for using interrupts
/// </summary>
/// <returns> 1 if it fails, 0 otherwise </returns>
int(enable_mouse_data)();

/// <summary>
/// Disables mouse so that it can return to its default state
/// </summary>
/// <returns></returns>
int(disable_mouse_data)();

/// <summary>
/// reads from the mouse
/// </summary>
/// <returns></returns>
void(read_from_mouse)();

/// <summary>
/// Moves de cursor according to the mouse packets recieved
/// </summary>
void mouse_movement();

/// <summary>
/// Empties the mouse and keyboard buffer (not working)
/// </summary>
void empty_buffer();

#endif
