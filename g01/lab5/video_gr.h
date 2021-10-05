#include <lcom/lcf.h>

int (vg_draw_rectangle)	(	uint16_t 	x, uint16_t 	y, uint16_t 	width, uint16_t 	height,uint32_t color );

void (double_buffer)();

void *(vg_init)(uint16_t mode);
int (vg_draw_pixel) (uint16_t x, uint16_t y, uint32_t color);

void(draw_sprite)(xpm_image_t img, uint8_t *sprite,int x, int y);

int (vbe_get_mode_info_custom)(uint16_t mode, vbe_mode_info_t *vmi_p);

