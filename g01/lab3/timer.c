#include "i8042.h"
#include <lcom/timer.h>
int hook_id_timer = 0;
int counter = 0;

int(timer_unsubscribe_int)() {
  //call sys_irq_
  if (sys_irqrmpolicy(&hook_id_timer) != OK) {
    return 1;
  };
  return OK;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  hook_id_timer = IRQ0;
  //call sys_irq_setpolicy
  int policy = IRQ_REENABLE;
  int IRQ_line = IRQ0;

  if (sys_irqsetpolicy(IRQ_line, policy, &hook_id_timer) != OK) {
    return 1;
  };

  return OK;
}

void(timer_int_handler)() {
  counter++;
}
