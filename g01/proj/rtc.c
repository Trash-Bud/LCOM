#include <lcom/lcf.h>
#include "rtc.h"

/// <summary>
/// IRQ Line for the RTC
/// </summary>
#define IRQ8 8

/// <summary>
/// Highscore date
/// </summary>
struct Date date;

/// <summary>
/// rtc hook id
/// </summary>
int hook_id_rtc = 3;

int rtc_subscribe(){
    if (sys_irqsetpolicy(IRQ8, IRQ_REENABLE, &hook_id_rtc)) return 1;
    return 0;
}
int rtc_unsubscribe(){
  if (sys_irqrmpolicy(&hook_id_rtc) != OK) return 1;
  return 0;
}

void rtc_ih() {
	uint32_t data;
    data = read_rtc(REGISTER_C);
}

int rtc_enable_update(){
    uint32_t data;
    data = read_rtc(REGISTER_B);
    
    data |= UIE;

    sys_outb(ADDR_REG, REGISTER_B);
    
    sys_outb(DATA_REG, data);
    
    return 0;
    
}

int rtc_disable_update(){
    uint32_t data;
    data = read_rtc(REGISTER_B);
    
    data &= ~UIE;

    sys_outb(ADDR_REG, REGISTER_B);
    
    sys_outb(DATA_REG, data);
    
    return 0;
}

int(read_rtc)(uint8_t reg) {
  uint32_t data;
  if (sys_outb(ADDR_REG, reg))
    return 1;

  if (sys_inb(DATA_REG, &data))
    return 1;

  return data;
}

int (rtc_get_date)() {

	uint32_t regA;

	do {
		regA = read_rtc(REGISTER_A);

		if(regA == RTC_ERROR) {
			return -1;
		}

	} while((regA & UIP) == UIP);


    date.year = read_rtc(YEAR_REGISTER);
    date.day = read_rtc(DAY_REGISTER);
    date.hour = read_rtc(HOUR_REGISTER);
    date.minute = read_rtc(MINUTE_REGISTER);
    date.month = read_rtc(MONTH_REGISTER);
    date.second = read_rtc(SECOND_REGISTER);
    
  

	if( date.year == RTC_ERROR || date.month == RTC_ERROR || date.day == RTC_ERROR || date.hour == RTC_ERROR || date.minute == RTC_ERROR || date.second == RTC_ERROR) {
		return -1;
	}

	return 0;
}

