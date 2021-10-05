#ifndef VIDEO_GR_H
#define VIDEO_GR_H

#include <lcom/lcf.h>
#include "logic.h"
#include "rtc.h"

#define BASE_ADDRESS 0

#define MiB (1 << 20)

/// <summary> 
/// Draws a rectangle.
/// </summary>
/// <param name="x"></param> position in x of the left upper corner of the rectangle
/// <param name="y"></param> position in y of the left upper corner of the rectangle
/// <param name="width"></param> width of the rectangle
/// <param name="height"></param> height of the rectangle
/// <param name="color"></param> color of the rectangle
/// <returns> 0 always </returns>
int (vg_draw_rectangle)	(	uint16_t 	x, uint16_t 	y, uint16_t 	width, uint16_t 	height,uint32_t color );

/// <summary>
/// Copies the content in the buffer to the video memory.
/// </summary>
/// <returns></returns>
void (double_buffer)();

/// <summary>
/// Initializes video mode
/// </summary>
/// <param name="mode"></param> mode to initialize in
/// <returns> NULL if the memory allocation fails, the video memories' adress otherwise </returns>
void *(vg_init)(uint16_t mode);

/// <summary>
/// Draws a pixel
/// </summary>
/// <param name="x"></param> position of the pixel in x
/// <param name="y"></param> position of the pixel in y
/// <param name="color"></param> color of the pixel
/// <returns> 1 if x and/ or  y are not within the resolution, 0 otherwise </returns>
int (vg_draw_pixel) (uint16_t x, uint16_t y, uint32_t color);

/// <summary>
/// Draws a sprite (the sprite itself already specifies its position, width and height).
/// </summary>
/// <param name="sprite"></param> sprite to draw
/// <returns></returns>
void(draw_sprite)(struct Sprite sprite);

/// <summary>
/// Gets info for the video mode and stores it in the variable vmi_p.
/// </summary>
/// <param name="mode"></param> current mode.
/// <param name="vmi_p"></param> variable that stores the mode info
/// <returns></returns>
int (vbe_get_mode_info_custom)(uint16_t mode, vbe_mode_info_t *vmi_p);

/// <summary>
/// Draws an horizontal line.
/// </summary>
/// <param name="x"></param> starting x coordinate of the line
/// <param name="y"></param> starting y coordinate of the line
/// <param name="len"></param> lenght of the line
/// <param name="color"></param> color of the line
/// <returns> 0 </returns>
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/// <summary>
/// Erased a sprite.
/// </summary>
/// <param name="sprite"></param> sprite to erase.
/// <returns></returns>
void(erase_sprite)(struct Sprite sprite);

/// <summary>
/// Draws a sprite in a specific color.
/// </summary>
/// <param name="sprite"></param> sprite to draw.
/// <param name="color1"></param> color to draw the sprite in.
/// <returns></returns>
void(draw_sprite_in_color)(struct Sprite sprite, uint32_t color1);

/// <summary>
/// Draws the buttons of the menu.
/// </summary>
/// <param name="menu"></param> menu to draw (array of sprites).
/// <param name="mode"></param> video mode.
void draw_menu_buttons(struct Sprite menu[],int mode);

/// <summary>
/// Writes numbers to the screen.
/// The numbers are written from the right to the left.
/// Uses the big number sprites.
/// </summary>
/// <param name="number"></param> number to write
/// <param name="x"></param> x of the left superior corner of the last digit
/// <param name="y"></param> y of the left superior corner of the last digit
/// <param name="color"></param> color to draw the numbers in
void write_number_to_screen(int number,int x, int y, int color);

/// <summary>
/// Writes numbers to the screen.
/// The numbers are written from the right to the left.
/// Uses the small number sprites.
/// </summary>
/// <param name="number"></param> number to write
/// <param name="x"></param> x of the left superior corner of the last digit
/// <param name="y"></param> y of the left superior corner of the last digit
/// <param name="color"></param> color to draw the numbers in
void write_small_number_to_screen(int number, int x, int y, int color);

/// <summary>
/// Writes a word to the screen.
/// Writes from left to right.
/// </summary>
/// <param name="word"></param> word to write
/// <param name="size"></param> size of the word (number of characters)
/// <param name="x"></param> x of the left superior corner of the first digit
/// <param name="y"></param> y of the left superior corner of the first digit
/// <param name="color"></param> color to draw the letters in
void write_word_to_screen(char word[],int size,int x, int y, int color);

/// <summary>
/// Writes a date to the screen in the format: dd-mm-yy     hh:mm:ss
/// </summary>
/// <param name="date"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="color"></param>
void write_date_to_screen(struct Date date,int x, int y, int color);

/// <summary>
/// Loads the sprites for specified mode and alters the global variable type.
/// </summary>
/// <param name="mode"></param> video mode.
/// <returns></returns>
void(load_sprites)(uint16_t mode);

#endif
