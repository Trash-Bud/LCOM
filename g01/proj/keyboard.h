#ifndef KEYBOARD_H
#define KEYBOARD_H

/// <summary>
/// Subscribes interrupts for the keyboard
/// </summary>
/// <returns> 1 if subscribe fails, 0 otherwise </returns>
int kbd_subscribe();

/// <summary>
/// Unsubscribed interrupts fot the keyboard
/// </summary>
/// <returns> 1 if subscribe fails, 0 otherwise </returns>
int kbd_unsubscribe();

/// <summary>
/// Assembles the scancode for printing and prints it
/// Function cannot fail
/// </summary>
void keyboard_print_scancode();

/// <summary>
/// Similair to interrup handler but here it runs until it outputs a scancode since with polling it won't time out the IH
/// </summary>
/// <returns> 1 if it fails, 0 otherwise </returns>
int kbd_read();

/// <summary>
/// Passes scan code through a global variable scancode
///In case of an error returns immidiatly with an error message
/// </summary>
void kbd_ih();

#endif
