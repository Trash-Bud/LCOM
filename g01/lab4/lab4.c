// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "mouse.h"

extern uint32_t total_packets;
extern bool reading_error;
extern int counter;
extern int counter_timer;
extern struct packet packet1;
int counter_exit = 0, x_displacement = 0, y_displacement = 0;
extern uint8_t read_packet;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt) {

  if (enable_mouse_data() != 0)
    return 1;
  uint8_t bit_no = 1;
  uint32_t irq_set = BIT(bit_no);

  kbc_subscribe();

  int ipc_status;
  message msg;
  double r = 0;

  while (total_packets < cnt) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            mouse_ih(); //calls interrupt handler
            if (reading_error == true && counter != 2) {
              continue;
            }
            else if (reading_error == true && counter == 2) {
              reading_error = false;
            }
            else
              print_mouse_packet(); //prints scancode
          }
          break;
        default: break;
      }
    }
  }

  kbc_unsubscribe();

  if (disable_mouse_data() != 0)
    return 1;

  return 0;
}

int(mouse_test_async)(uint8_t idle_time) {

  uint8_t bit_no_mouse = 1;
  uint8_t bit_no_timer = IRQ0;
  uint32_t irq_set_mouse = BIT(bit_no_mouse);
  uint32_t irq_set_timer = BIT(bit_no_timer);
  if (enable_mouse_data() != 0)
    return 1;
  kbc_subscribe();
  timer_subscribe_int(&bit_no_timer);

  int ipc_status;
  message msg;
  double r = 0;

  while (counter_timer < idle_time * 60) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                                   /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set_mouse) { /* subscribed interrupt */
            counter_timer = 0;
            mouse_ih(); //calls interrupt handler
            if (reading_error == true && counter != 2) {
              continue;
            }
            else if (reading_error == true && counter == 2) {
              reading_error = false;
            }
            else {
              print_mouse_packet();
            }
          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
          }
          break;
        default: break;
      }
    }
  }
  kbc_unsubscribe();
  disable_mouse_data();
  timer_unsubscribe_int();
  return 0;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {

  if (enable_mouse_data() != 0)
    return 1;
  uint8_t bit_no = 1;
  uint32_t irq_set = BIT(bit_no);
  int counter_exit = 0;

  kbc_subscribe();

  int ipc_status;
  message msg;
  double r = 0;

  while (counter_exit != 6) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            mouse_ih(); //calls interrupt handler
            if (reading_error == true && counter != 2) {
              continue;
            }
            else if (reading_error == true && counter == 2) {
              reading_error = false;
            }
            else {
              print_mouse_packet(); //prints scancode
              if (counter == 0) {
                printf("in %d\n", counter_exit);
                if (packet1.lb && counter_exit == 0) {
                  counter_exit = 1;
                }
                else if (packet1.lb && (packet1.delta_x + tolerance) >= 0 && (packet1.delta_y + tolerance) >= 0 && counter_exit == 1) {
                  x_displacement += packet1.delta_x;
                  printf ("disp %d\n", x_displacement);
                  if (x_displacement >= x_len) {
                    counter_exit = 2;
                  }
                }
                else if (counter_exit == 1){
                  counter_exit = 0;
                  x_displacement = 0;
                }
                else if (!packet1.lb && counter_exit == 2) {
                  counter_exit = 3;
                  x_displacement = 0;
                }
                else if (packet1.rb && counter_exit == 3) {
                  counter_exit = 4;

                }
                else if (packet1.rb && (packet1.delta_x + tolerance) >= 0 && (packet1.delta_y - tolerance) <= 0 && counter_exit == 4) {
                  x_displacement += packet1.delta_x;
                  if (x_displacement >= x_len) {
                    counter_exit = 5;
                  }
                }
                else if (counter_exit == 4){
                  x_displacement = 0;
                  counter_exit = 0;
                }
                else if (!packet1.rb && counter_exit == 5) {
                  if (packet1.lb){
                    counter_exit = 0;
                  }
                  counter_exit = 6;
                }
                else if (counter_exit == 5){
                  counter_exit = 0;
                }
              }
            }
          }
          break;
        default: break;
      }
    }
  }

  kbc_unsubscribe();

  if (disable_mouse_data() != 0)
    return 1;

  return 0;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt) {

  int count = 0;

  write_argument_to_mouse(DISABLE_MOUSE_DATA);

  write_argument_to_mouse(SET_REMOTE_MODE);

  while (total_packets < cnt) {

    write_argument_to_mouse(READ_DATA_MOUSE);

    while (count != 3) {
      mouse_ih();
      if (reading_error == true && counter != 2) {
        continue;
      }
      else if (reading_error == true && counter == 2) {
        reading_error = false;
      }
      else {
        print_mouse_packet();
      }
      count++;
    }
    count = 0;
    tickdelay(micros_to_ticks(period * 1000));
  }

  if (disable_mouse_data() != 0)
    return 1;

  uint8_t status;
  while (true) {
    if (util_sys_inb(STATUS_REGISTER, &status) != 0)
      return 1;
    if ((status & BIT(1)) == 0) {
      if (sys_outb(INPUT_BUFFER_COMMANDS, WRITE_COMMAND) != 0)
        return 1;
      break;
    }
  }
  while (true) {
    if (util_sys_inb(STATUS_REGISTER, &status) != 0)
      return 1;
    if ((status & BIT(1)) == 0) {
      if (sys_outb(INPUT_BUFFER_ARGUMENTS, minix_get_dflt_kbc_cmd_byte()) != 0)
        return 1;
      break;
    }
  }

  return 0;
}
