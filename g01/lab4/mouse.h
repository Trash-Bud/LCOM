#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>

int(kbc_subscribe)();
int(kbc_unsubscribe)();
void(mouse_ih)();
void (print_mouse_packet)();
int(write_argument_to_mouse)(uint8_t argument);
int(enable_mouse_data)();
int(disable_mouse_data)();
void(read_from_mouse)();


#endif
