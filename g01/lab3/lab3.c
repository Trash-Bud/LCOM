#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "keyboard.h"

extern uint8_t scancode;
extern int cnt;
extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g01/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g01/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {

  uint8_t bit_no = IRQ1;
  uint32_t irq_set = BIT(bit_no);

  kbc_subscribe();

  int ipc_status;
  message msg;
  double r = 0;
  printf("%d", scancode);

  while (scancode != ESCAPE) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            kbc_ih(); //calls interrupt handler
            kbc_print_scancode(); //prints scancode
          }
          break;
        default: break;
      }
    }
  }
  kbc_unsubscribe();

  kbd_print_no_sysinb(cnt); //prints thenumber of sys_inb used

  return 0;
}

int(kbd_test_poll)() {

  while(scancode != ESCAPE){ //pools and prints scancodes until ESC is pressed

    if (kbc_read() != 0) return 1;
    kbc_print_scancode();
  }

  //The polling method disables interrupts, therefore they have to be reactivated so that we can continue using the keyboard
  if (sys_outb(INPUT_BUFFER_COMMANDS,READ_COMMAND) != 0) return 1; //to be able to read the command bit that we need to write to the arguments' buffer we nedd first to write the read command to the Commands Buffer

  kbc_read(); //reading the command bit, it'll end up in the scancode variable since we are using the same function that we used to read scancodes

  if (sys_outb(INPUT_BUFFER_COMMANDS,WRITE_COMMAND) != 0) return 1; //to be able to write it we need to send the write command to the command buffer
  if (sys_outb(INPUT_BUFFER_ARGUMENTS,scancode|BIT(0)) != 0) return 1; //finaly we write the command bit to the arguments buffer


  kbd_print_no_sysinb(cnt);
  return OK;
}

int(kbd_test_timed_scan)(uint8_t idle) {
  uint8_t bit_no_kbd = IRQ1;
  uint8_t bit_no_timer = IRQ0;
  uint32_t irq_set_kbd = BIT(bit_no_kbd);
  uint32_t irq_set_timer = BIT(bit_no_timer);
  kbc_subscribe();
  timer_subscribe_int(&bit_no_timer);

  int ipc_status;
  message msg;
  double r = 0;
  printf("%d", scancode);

  while (scancode != ESCAPE) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set_kbd) { /* subscribed interrupt */
            kbc_ih(); //calls interrupt handler
            kbc_print_scancode();//prints scancode
            counter = 0;  //reset counter
          }
           if (msg.m_notify.interrupts & irq_set_timer) { 
              timer_int_handler();
              printf("Counter-> %d\n",counter);
              if(counter >= idle * 60){ //we know that the frequency is set to 60, so after idle * 60 cycles we hit our time
                  scancode = ESCAPE; //condiion to leave the loop
              }
          }

          break;
        default: break;
      }
    }
  }
  kbc_unsubscribe();
  timer_unsubscribe_int();

  kbd_print_no_sysinb(cnt); //prints thenumber of sys_inb used

  return 0;
}
