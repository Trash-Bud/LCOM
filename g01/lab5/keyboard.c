#include <lcom/lcf.h>

#include "i8042.h"
#include "keyboard.h"
#include <stdint.h>


int hook_id_kbd = 0;
uint8_t scancode = 0;

/*Subscribes the interrupt
Error -> returns 1
Success -> returns 0
*/
int(kbc_subscribe)() { 

  hook_id_kbd = IRQ1; //hook_id corresponds to the IRQ1 line because that's the interrupt line for the keyboard

  if (sys_irqsetpolicy(IRQ1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kbd) != 0) return 1;
  return 0;
}


/*Unsubscribes the interrupt
Error -> returns 1
Success -> returns 0
*/
int(kbc_unsubscribe)() {

  if (sys_irqrmpolicy(&hook_id_kbd) != OK) return 1;
  return 0;
}



/*Interruption handler,
Void function does not return anything
Passes scan code through a global variable scancode
In case of an error returns immidiatly with an error message
*/
void(kbc_ih)() {

  uint8_t stat;

  for (int i = 0; i < 2; i++) { //number of iterations that does not cause the program to timeout
    if (util_sys_inb(STATUS_REGISTER, &stat) != 0) { //reads status from the status register
      printf("Error! Couldn't read status from keyboard.\n");
      return;
    }

    if (stat & OUT_BUFF) { //checks if there is anything inside the output buffer
      if (util_sys_inb(OUTPUT_BUFFER, &scancode) != 0) { //reads scancode from the output buffer
        printf("Error! Couldn't read scancode from buffer.\n");
        return;
      }
      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) == 0) { //If there are no parity error (bit 7) or time out (bit 6) the scancode is valid and the function returns
        return;
      }
      else{
        printf("Error! Parity error or Time Out recieved.\n");
        return;
      }
    }
    tickdelay(micros_to_ticks(WAIT_KBC)); //waits 20ms 
  }
}

/*Assembles the scancode for printing and prints it
Function cannot fail
*/
void (kbc_print_scancode)() {
  //NOTE: the buffer only read 8bits (1B) at a time however scancodes may have 2 bytes

  uint8_t scancodes[2]; 
  bool makecode = false; // makecode = false means that the scancode is a breakcode, 
  uint8_t bytes = 1;

  if (scancode == 0xE0) { //if the scancode obtaines is the 8 more significative bites of a 2B scancode then it equals 0xE0
    bytes = 2; //sets bytes to two
    scancodes[1] = scancode; 
    return; //returs so that the interruption handler may read the second byte
  }

  //if the scancode is only one byte long or if we are reading the less significative byte of a 2 byte scan code
  if ((scancode & 0x80) == 0) { //makecodes have the 7th byte at 1
    makecode = true;
  }

  scancodes[0] = scancode;

  kbd_print_scancode(makecode, bytes, scancodes); 

  //returns the values to their default
  bytes = 1;
  makecode = false;
}

/*Reads scancodes
Similair to interrup handler but here it runs until it outputs a scancode since with polling it won't time out the IH
Error -> returns 1
Success -> returns 0
*/
int (kbc_read)(){
  uint8_t stat;

  while (true){
    if (util_sys_inb(STATUS_REGISTER, &stat) != OK) {
      printf("Couldn't read status from keyboard.\n");
      return 1;
    }

    if (stat & OUT_BUFF) {
      if (util_sys_inb(OUTPUT_BUFFER, &scancode) != OK) {
        printf("Couldn't read scancode from buffer.\n");
        return 1;
      }
      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) == 0) { 
        return 0;
      }
      else
        return 1;
    }
  }
}
