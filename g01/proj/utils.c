#include <lcom/lcf.h>

#include <stdint.h>

int cnt = 0;

/// <summary>
/// Get's least significant bit.
/// </summary>
/// <param name="val"></param> value 
/// <param name="lsb"></param> variable which return the lsb
/// <returns> 0 </returns>
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  uint16_t LSB = val & 0x00FF;
  *lsb = (uint8_t) LSB;
  return 0;
}

/// <summary>
/// Get's most significant bit.
/// </summary>
/// <param name="val"></param> value
/// <param name="msb"></param> variable which return the msb
/// <returns></returns>
int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  uint16_t MSB = val & 0xFF00;
  MSB = MSB >> 8;
  *msb = (uint8_t) MSB;
  return 0;
}

/// <summary>
/// sys_inb which returns in the variable value only the 8 lsb of the value stored in the port.
/// </summary>
/// <param name="port"></param> port to read
/// <param name="value"></param> variable to return the 8 bit value
/// <returns></returns>
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
