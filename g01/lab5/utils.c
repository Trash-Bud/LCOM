#include <lcom/lcf.h>
#include "utils.h"
#include <stdint.h>

int cnt = 0;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  uint16_t LSB = val & 0x00FF;
  *lsb = (uint8_t) LSB;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  uint16_t MSB = val & 0xFF00;
  MSB = MSB >> 8;
  *msb = (uint8_t) MSB;
  return 0;
}

int(util_sys_inb)(int port, uint8_t *value) {

  uint32_t val = 0;

  int a = sys_inb(port, &val);
#ifdef LAB3
  cnt++;
#endif

  if (a == 0) {
    *value = (uint8_t) val;
  }
  else {
    return 1;
  }

  return 0;
}
