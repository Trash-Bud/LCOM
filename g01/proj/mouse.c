#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "mouse.h"
#include "logic.h"

/// <summary>
/// struct wherw the mouse packet is stored
/// </summary>
struct packet packet1;
/// <summary>
/// data read from the mouse
/// </summary>
uint8_t read_packet;
/// <summary>
/// true if the mouse is synced, false otherwise
/// </summary>
bool is_sync = false;
/// <summary>
/// counter for the mouse
/// used for packet assembly
/// </summary>
int counter = 0;
/// <summary>
/// hook id of the mouse
/// </summary>
int hook_id_mouse;
/// <summary>
/// true if the is a reading error, fals eotherwise
/// </summary>
bool reading_error = false;
extern struct Sprite mouse;
extern vbe_mode_info_t vmi_p;


/*Subscribes the interrupt
Error -> returns 1
Success -> returns 0
*/
int(kbc_subscribe)() {

  hook_id_mouse = 2;
  
  if (sys_irqsetpolicy(IRQ12, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse) != 0) return 1;
  return 0;
}

/*Unsubscribes the interrupt
Error -> returns 1
Success -> returns 0
*/
int(kbc_unsubscribe)() {
  if (sys_irqrmpolicy(&hook_id_mouse) != OK)
    return 1;
  return 0;
}


int(write_argument_to_mouse)(uint8_t argument){
  uint8_t acknow;
  uint8_t status;

  while(true){
    if(util_sys_inb(STATUS_REGISTER, &status)!= 0) return 1;
    if((status & BIT(1)) == 0) {
      if (sys_outb(INPUT_BUFFER_COMMANDS, ISSUE_COMMAND_TO_THE_MOUSE) != 0) return 1;
      break;
    }
  }

  while(true){
    if(util_sys_inb(STATUS_REGISTER, &status)!= 0) return 1;
    if((status & BIT(1)) == 0) { 
      if (sys_outb(INPUT_BUFFER_ARGUMENTS,argument)!= 0) return 1;  

      if (util_sys_inb(OUTPUT_BUFFER,&acknow) != 0) return 1;
      if(acknow == IS_OK) return 0;
    }
  }

}


void (empty_buffer)(){
  uint8_t data;
  uint8_t stat;
  while (true) {
    util_sys_inb(STATUS_REGISTER, &stat);
    util_sys_inb(OUTPUT_BUFFER, &data);
    if (stat && OUT_BUFF)
      break;
  }
  
}

int(enable_mouse_data)(){

  if (write_argument_to_mouse(SET_STREAM_MODE)) return 1;
  if (write_argument_to_mouse(ENABLE_MOUSE_DATA)) return 1;

  return 0;
}

int(disable_mouse_data)(){

  if (write_argument_to_mouse(DISABLE_MOUSE_DATA)!= 0) return 1;
  if (write_argument_to_mouse(SET_STREAM_MODE)!= 0) return 1;
  return 0;
}

int (kbc_read)(){
  uint8_t stat;

  while (true){
    if (util_sys_inb(STATUS_REGISTER, &stat) != OK) {
      printf("Couldn't read status from keyboard.\n");
      return 1;
    }

    if (stat & OUT_BUFF) {
      if (util_sys_inb(OUTPUT_BUFFER, &read_packet) != OK) {
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

/*Interruption handler,
Void function does not return anything
Passes scan code through a global variable scancode
In case of an error returns immidiatly with an error message
*/
void(mouse_ih)() {

  uint8_t stat;

  while(true) { //number of iterations that does not cause the program to timeout

    if (util_sys_inb(STATUS_REGISTER, &stat) != 0) { //reads status from the status register
      printf("Error! Couldn't read status from keyboard.\n");
      break;
    }

    if (stat & (OUT_BUFF | AUX_BIT) ) { //checks if there is anything inside the output buffer
      
      if (util_sys_inb(OUTPUT_BUFFER, &read_packet) != 0) { //reads scancode from the output buffer
        printf("Error! Couldn't read scancode from buffer.\n");
        break;
      }

      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) == 0) { //If there are no parity error (bit 7) or time out (bit 6) the scancode is valid and the function returns
        if (reading_error == true){
          counter ++;
        }
        return;
      }
      else {

        printf("Error! Parity error or Time Out recieved.\n");
        break;
      }
    }

    tickdelay(micros_to_ticks(WAIT_KBC)); //waits 20ms
  }
  reading_error = true;
  counter++;
}


/*Assembles the scancode for printing and prints it
Function cannot fail
*/
void(assemble_mouse_packet)() {
  
  if (is_sync == false) {

    if ((read_packet & 0x08) == 0) {
      printf("Mouse out of sync please click again!");
      return;
    }
    else
      is_sync = true;
  }
  

  if (counter == 0) {
    
    packet1.bytes[0] = read_packet;
    counter++;
    packet1.y_ov = (packet1.bytes[0] & BIT(7));
    packet1.x_ov = packet1.bytes[0] & BIT(6);
    packet1.mb = packet1.bytes[0] & BIT(2);
    packet1.rb = packet1.bytes[0] & BIT(1);
    packet1.lb = packet1.bytes[0] & BIT(0);

    return;
  }

  if (counter == 1) {
  
    packet1.bytes[1] = read_packet;
    counter++;
    if ((packet1.bytes[0] & BIT(4)) != 0) {
      packet1.delta_x = (uint16_t)(packet1.bytes[1] - 256);
    }
    else
      packet1.delta_x = (uint16_t) packet1.bytes[1];
    return;
  }

  if (counter == 2) {

    packet1.bytes[2] = read_packet;
    if ((packet1.bytes[0] & BIT(5)) != 0){
      packet1.delta_y = (uint16_t) (packet1.bytes[2] - 256);
    }
    else
      packet1.delta_y = (uint16_t) packet1.bytes[2];
 
    counter = 0;
    
  }
}


void mouse_movement(){
  if  (packet1.x_ov || packet1.y_ov){
    return;
  }

  mouse.y -= packet1.delta_y;
  mouse.x += packet1.delta_x;


  if(mouse.x + mouse.width > vmi_p.XResolution){
    mouse.x = vmi_p.XResolution - mouse.width -5;
  }else if(mouse.x < 0){
    mouse.x = 5;
  }else if(mouse.y + mouse.height > vmi_p.YResolution){
    mouse.y = vmi_p.YResolution - mouse.height - 5;
  }
  else if(mouse.y < 0){
    mouse.y = 5;
  }

  packet1.delta_x = 0;
  packet1.delta_y = 0;

}
