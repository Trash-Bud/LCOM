#include "i8254.h"
#include <lcom/lab2.h>
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
extern int counter;
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t st = 0; //status
  if (timer_get_conf(timer, &st) == 0) {
    printf("timer get conf OK \n");
    if (timer_display_conf(timer, st, field) == 0)
      printf("timer display conf OK \n");
    else {
      printf("timer display conf failed \n");
      return 1;
    }
  }
  else {
    printf("timer get conf failed \n");
  }

  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  timer_set_frequency(timer, freq);

  return 0;
}

int(timer_test_int)(uint8_t time) {
  //subscribe int
  uint8_t bit_no = TIMER0_IRQ;
  uint32_t irq_set = BIT(bit_no);

  timer_subscribe_int(&bit_no);
  //get irq_set
  int ipc_status;
  message msg;
  double r = 0;
  //assume-se que a frequência é 60Hz, mas vamos colocá-la de qualquer modo
  int frequency = 60;
  if (timer_set_frequency(0, frequency) != 0) {
    timer_unsubscribe_int();
    return 1;
  };

  while (counter < frequency * time) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            timer_int_handler();
            if (counter % frequency == 0) {
              timer_print_elapsed_time();
            }
          }
          break;
        default:
          break;
      }
    }
  }

  //unsubscribe_int
  timer_unsubscribe_int();
  return 0;
}
