#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>

/// <summary>
/// Struct which represents a date
/// </summary>
struct Date {
  /// <summary>
  /// Seconds 
  /// </summary>
  unsigned int second;
  /// <summary>
  /// Minutes
  /// </summary>
  unsigned int minute;
  /// <summary>
  /// Hours
  /// </summary>
  unsigned int hour;
  /// <summary>
  /// Day
  /// </summary>
  unsigned int day;
  /// <summary>
  /// Month
  /// </summary>
  unsigned int month;
  /// <summary>
  /// Year
  /// </summary>
  unsigned int year;
};

/// <summary>
/// irq line para o RTC
/// </summary>
#define IRQ8 8 

/// <summary>
/// flag que simboliza que ocorreu um erro a ler dos registos do RTC 
/// </summary>
#define RTC_ERROR 0xFFFFFFFF

/// <summary>
/// register to write the register you wish to read from the RTC
/// </summary>
#define ADDR_REG 0x70 

/// <summary>
/// register C
/// </summary>
#define REGISTER_C 12

/// <summary>
/// register B
/// </summary>
#define REGISTER_B 11

/// <summary>
/// register A
/// </summary>
#define REGISTER_A 10

/// <summary>
/// usado para transferir os dados do registo lido para uma variável
/// </summary>
#define DATA_REG 0x71 

/// <summary>
/// bit which to inhibits/allows updates of time/date registers
/// </summary>
#define UIP	BIT(7)

/// <summary>
/// register which holds the seconds field of the current date
/// </summary>
#define SECOND_REGISTER	0x00	

/// <summary>
/// register which holds the minute field of the current date
/// </summary>
#define MINUTE_REGISTER	0x02	

/// <summary>
/// register which holds the hour field of the current date
/// </summary>
#define HOUR_REGISTER 0x04	

/// <summary>
/// register which holds the day field of the current date
/// </summary>
#define DAY_REGISTER 0x07	
/// <summary>
/// register which holds the month field of the current date
/// </summary>
#define MONTH_REGISTER 0x08	
/// <summary>
/// register which holds the year field of the current date
/// </summary>
#define YEAR_REGISTER 0x09	

/// <summary>
/// used to enable/disable update interrupts on the register B
/// </summary>
#define UIE BIT(4)

/// <summary>
/// rtc interrupt handler
/// </summary>
void rtc_ih();

/// <summary>
/// Subscribes rtc interrupts
/// </summary>
/// <returns> 1 if it fails, 0 otherwise </returns>
int rtc_subscribe();

/// <summary>
/// Unsubscribes rtc interrupts
/// </summary>
/// <returns> 1 if it fails, 0 otherwise </returns>
int rtc_unsubscribe();

/// <summary>
/// Enables update mode of the rtc
/// </summary>
/// <returns> 0 </returns>
int rtc_enable_update();

/// <summary>
/// Disables update mode of the rtc
/// </summary>
/// <returns> 0 </returns>
int rtc_disable_update();

/// <summary>
/// Reads from the rtc
/// </summary>
/// <param name="reg"></param> register to read from
/// <returns> content read from the register </returns>
int(read_rtc)(uint8_t reg);

/// <summary>
/// Gets the current date (dd, mm, yy, hh, mm, ss) and puts it in the global variable date.
/// </summary>
/// <returns> -1 if it fails, 0 otherwise </returns>
int (rtc_get_date)();


#endif
