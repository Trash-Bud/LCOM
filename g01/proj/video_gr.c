#include <lcom/lab5.h>
#include <lcom/lcf.h>

#include "i8042.h"
#include "video_gr.h"
#include "power_up.h"
#include "UI_elements.h"

/// <summary>
/// video mem address
/// </summary>
static char *video_mem;
/// <summary>
/// intemediate buffer to be copyed to the video mem
/// </summary>
static char *buffer;
/// <summary>
/// Variable with the mode info
/// </summary>
vbe_mode_info_t vmi_p;
extern struct Player player1, player2;
extern struct Ball ball_;
extern struct Sprite score;
extern struct Sprite mouse;
extern struct Sprite big_numbers_and_letters[36];
extern struct Sprite small_numbers[12];
extern struct Sprite MainMenuSprites[7];
extern struct Sprite ResolutionsMenu[6];
extern struct Sprite GameTypeTimeLimit[4];
extern struct Sprite GameTypePointLimit[4];
extern struct Sprite GameType[4];
extern struct Sprite PauseScreen[4];
extern struct Sprite WinScreen[8];
extern struct Sprite HighScores[5];
extern struct Sprite HoverButtons[16];
extern int size_menu;
extern int highest_score;
extern char highest_score_name[25];
extern int size_of_highscore_name;
extern struct Sprite CurrentMenu[8];
extern int character_number;
extern char name[25];
extern int point_limit;
extern int max_time;
extern struct Date date;
extern struct PowerUp Power_ups[3];

extern enum xpm_image_type type;

void write_word_to_screen(char word[],int size,int x, int y, int color){
  for(int i =0; i < size; i++){
    if(word[i] < 65){
        big_numbers_and_letters[(int)(word[i]) -22].x = x + i * big_numbers_and_letters[0].width + 1;
         big_numbers_and_letters[(int)(word[i]) -22].y = y;
        draw_sprite_in_color(big_numbers_and_letters[(int)(word[i]) -22 ],color);
    }
    else{
      big_numbers_and_letters[(int)(word[i]) -65].x = x + i * big_numbers_and_letters[0].width + 1;
      big_numbers_and_letters[(int)(word[i]) -65].y = y;
      draw_sprite_in_color(big_numbers_and_letters[(int)(word[i]) - 65],color);
    }
  }
}

void draw_menu_buttons(struct Sprite menu[],int mode){
  vg_draw_rectangle(0, 0, vmi_p.XResolution, vmi_p.YResolution, 0);
  draw_sprite(ball_.sprite);
  draw_sprite(player1.sprite[player1.current_sprite]);
  draw_sprite(player2.sprite[player2.current_sprite]);
  vg_draw_hline(0, score.height + score.y + 2, vmi_p.XResolution, 0xffffff);
  draw_sprite(score);
  for(int i = 0; i < size_menu ; i++){
     if(checkIfEqual(menu,WinScreen,8)){
      if( (i == 1 || i == 2) && player1.score <= highest_score && player2.score <= highest_score ){
          continue;
      }
      if( i== 5){
        continue;
      }
      if(player1.score > player2.score && (i == 4 || i == 7)){
          continue;
      }else if(player2.score > player1.score && (i == 3 || i == 7)){
          continue;      
      }else if(player2.score == player1.score && (i == 3 || i == 4) ) {
          continue;
      }
    }
     draw_sprite(menu[i]);
     
  }

  int highscore_x, highscore_y, name_x, name_y, date_x,date_y, name_highscore_x, name_highscore_y, time_limit_input_x, time_limit_input_y;

  switch(mode){
      case 0x14C:
        highscore_x = 256;
        highscore_y = 304;
        name_x = 446;
        name_y = 303;
        date_x = 98;
        date_y = 364;
        name_highscore_x = 180;
        name_highscore_y = 575;
        time_limit_input_x = 222;
        time_limit_input_y = 375;
        break;
      case 0x11A:
        highscore_x = 286 ;
        highscore_y = 348 ;
        name_x = 497;
        name_y = 347;
        date_x = 110 ;
        date_y = 419;
        name_highscore_x = 212;
        name_highscore_y = 686;
        time_limit_input_x = 248;
        time_limit_input_y = 465;
        break;
      case 0x115:
        highscore_x = 200;
        highscore_y =  210;
        name_x = 323 ;
        name_y = 230 ;
        date_x = 110;
        date_y = 260;
        name_highscore_x = 165;
        name_highscore_y = 410;
        time_limit_input_x = 179;
        time_limit_input_y = 285;
        break;
      case 0x110:
        highscore_x = 160 ;
        highscore_y =  159;
        name_x = 256 ;
        name_y =159 ;
        date_x = 80;
        date_y = 192 ;
        name_highscore_x = 129;
        name_highscore_y = 324;
        time_limit_input_x = 140;
        time_limit_input_y = 213;
        break;
    }

  if(checkIfEqual(CurrentMenu,GameTypeTimeLimit,4)){
      write_number_to_screen(max_time,time_limit_input_x + character_number * big_numbers_and_letters[0].width,time_limit_input_y,0);              
  }
  else if (checkIfEqual(CurrentMenu, GameTypePointLimit, 4)) {
    write_number_to_screen(point_limit, time_limit_input_x + character_number * big_numbers_and_letters[0].width, time_limit_input_y, 0);
  }
  else if (checkIfEqual(CurrentMenu, HighScores, 5)) {
    write_number_to_screen(highest_score, highscore_x, highscore_y, 0);
    write_word_to_screen(highest_score_name, size_of_highscore_name, name_x, name_y, 0);
    write_date_to_screen(date, date_x, date_y, 0);
  }
  else if (checkIfEqual(CurrentMenu, WinScreen, 8)) {
    write_word_to_screen(name, character_number, name_highscore_x, name_highscore_y, 0);
  }
}


void write_number_to_screen(int number,int x, int y, int color){
  int temp_int = number;
  while(temp_int > 0){
    big_numbers_and_letters[temp_int % 10 + 26].y = y;
    big_numbers_and_letters[temp_int % 10 + 26].x = x;
    draw_sprite_in_color(big_numbers_and_letters[temp_int % 10+ 26],color);
    x -= big_numbers_and_letters[0].width;
    temp_int = temp_int / 10;
  }
  double_buffer();
}

void write_date_to_screen(struct Date date,int x, int y, int color){
  small_numbers[0].y = y + 5;
  small_numbers[1].y = y + 2;
  x = x + small_numbers[3].width;
  write_small_number_to_screen(date.day,x,y,color);
  x = x + small_numbers[3].width + 3;
  small_numbers[0].x = x;
  draw_sprite(small_numbers[0]);
  x = x + small_numbers[0].width + small_numbers[3].width + 3;
  write_small_number_to_screen(date.month,x,y,color);
  x = x + small_numbers[3].width + 3;
  small_numbers[0].x = x;
  draw_sprite(small_numbers[0]);
  x = x + small_numbers[0].width + small_numbers[3].width + 3;
  write_small_number_to_screen(date.year,x,y,color);
  x = x + 30;
  x = x + small_numbers[3].width;
  write_small_number_to_screen(date.hour,x,y,color);
  x = x + small_numbers[3].width + 3;
  small_numbers[1].x = x;
  draw_sprite(small_numbers[1]);
  x = x + small_numbers[1].width + small_numbers[3].width + 3;
  write_small_number_to_screen(date.minute,x,y,color);
  x = x + small_numbers[3].width + 3;
  small_numbers[1].x = x;
  draw_sprite(small_numbers[1]);
  x = x + small_numbers[1].width + small_numbers[3].width + 3;
  write_small_number_to_screen(date.second,x,y,color);
}

void write_small_number_to_screen(int number, int x, int y, int color){
  int temp_score = number;
  if(number == 0){
   small_numbers[2].y = y;
   small_numbers[2].x = x;
   draw_sprite_in_color(small_numbers[2],color);
  }
  int x_real = x;

  while(temp_score > 0){
    small_numbers[temp_score % 10 + 2].y = y;
    small_numbers[temp_score % 10 + 2].x = x_real;
    draw_sprite_in_color(small_numbers[temp_score % 10 + 2],color);
    x_real -= small_numbers[temp_score % 10  + 2].width + 1;
    temp_score = temp_score / 10;
  }
  if(number < 10){
    small_numbers[2].y = y;
    small_numbers[2].x = x_real;
    draw_sprite_in_color(small_numbers[2], color);
  }
}

void *(vg_init)(uint16_t mode){
  struct minix_mem_range mr;
  unsigned int vram_base;  /* VRAM's physical addresss */
  unsigned int vram_size;  /* VRAM's size, but you can use the frame-buffer size, instead */
  int r;				    

  vbe_get_mode_info_custom(mode,&vmi_p);

  vram_base = vmi_p.PhysBasePtr;
  if(vmi_p.BitsPerPixel == 15){
     vram_size = vmi_p.XResolution * vmi_p.YResolution * 2;
  }
  else
  {
    vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel)/ 8);
  }
  
  //allocate space for our buffer
  buffer = (char *) malloc(vram_size);


  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d/n", r);

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  printf("VG INIT \n");
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
  reg86.bx = 1 << 14 | mode; //set bit 14: linear framebuffer
  if( sys_int86(&reg86) != OK ) {
    printf("vg_exit(): sys_int86() failed /n");
    return NULL;
  }         

  if(video_mem == MAP_FAILED){
    panic("couldn't map video memory");
    return NULL;
  }

  return video_mem;

}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x > vmi_p.XResolution || y > vmi_p.YResolution)
    return 1;

  if (vmi_p.BitsPerPixel == 15)
    memcpy(buffer + vmi_p.XResolution * y * 2 + x * 2, &color, 2);
  else {
    memcpy(buffer + vmi_p.XResolution * y * (vmi_p.BitsPerPixel / 8) + x * (vmi_p.BitsPerPixel / 8), &color, (vmi_p.BitsPerPixel / 8));
  }
  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    vg_draw_pixel(x + i, y, color);
  }
  return 0;
}

void(double_buffer)() {
  if (vmi_p.BitsPerPixel == 15) {
    memcpy(video_mem, buffer, vmi_p.XResolution * vmi_p.YResolution * 2);
  }
  else {
    memcpy(video_mem, buffer, vmi_p.XResolution * vmi_p.YResolution * (vmi_p.BitsPerPixel / 8));
  }
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++) {
    vg_draw_hline(x, y + i, width, color);
  }
  return 0;
}

void(draw_sprite)(struct Sprite sprite) {

  uint32_t color, red, green, blue, byte1, byte2;
  uint8_t * temp_sprite = sprite.sprite1;
  switch ((vmi_p.BitsPerPixel + 7) / 8) {
    case (1):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          if(xpm_transparency_color(type) != *(temp_sprite)){
            vg_draw_pixel(sprite.x + j, sprite.y + i, *(temp_sprite));
          }
          temp_sprite++;
        }
      }
      break;
    case (2):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          if (vmi_p.BitsPerPixel == 15) {
            byte1 = *(temp_sprite + 1) & 0xef;
          }
          else
          byte1 = *(temp_sprite + 1) & 0xff;
          byte2 = *(temp_sprite) &0xff;
          color = byte1 << 8 | byte2;
          if(xpm_transparency_color(type) != color){
            vg_draw_pixel(sprite.x + j, sprite.y + i, color);
          }
          temp_sprite += 2;
        }
      }
      break;
    case (3):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          red = *(temp_sprite + 2) & 0xff;
          green = *(temp_sprite + 1) & 0xff;
          blue = *(temp_sprite) &0xff;
          color = red << 16 | green << 8 | blue;
          if(xpm_transparency_color(type) != color){
            vg_draw_pixel(sprite.x + j, sprite.y + i, color);
          }
          temp_sprite += 3;
        }
      }
      break;
    case (4):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          byte1 = *(temp_sprite + 3) & 0xff;
          red = *(temp_sprite + 2) & 0xff;
          green = *(temp_sprite + 1) & 0xff;
          blue = *(temp_sprite) & 0xff;
          color = byte1 << 24 | red << 16 | green << 8 | blue;
          if(xpm_transparency_color(type) != color){
            vg_draw_pixel(sprite.x + j, sprite.y + i, color);
          }
          temp_sprite += 4;
        }
      }
      break;
    default:
      break;
  }
}

void(draw_sprite_in_color)(struct Sprite sprite, uint32_t color1) {

  uint32_t color, color2, red, green, blue, byte1, byte2;
  uint8_t *temp_sprite = sprite.sprite1;
  switch ((vmi_p.BitsPerPixel + 7) / 8) {
    case (1):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          if (xpm_transparency_color(type) != *(temp_sprite)) {
            vg_draw_pixel(sprite.x + j, sprite.y + i, color1);
          }
          temp_sprite++;
        }
      }
      break;
    case (2):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          if (vmi_p.BitsPerPixel == 15) {
            byte1 = color1 & 0xef00;
          }
          else
          byte1 = color1 & 0xff00;
          byte2 = color1 &0xff;
          color = byte1 << 8 | byte2;
          byte1 = *(temp_sprite + 1) & 0xff;
          byte2 = *(temp_sprite) &0xff;
          color2 = byte1 << 8 | byte2;
          if (xpm_transparency_color(type) != color2) {
            vg_draw_pixel(sprite.x + j, sprite.y + i, color1);
          }
          temp_sprite += 2;
        }
      }
      break;
    case (3):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          red = color1 & 0xff0000;
          green = color1 & 0xff00;
          blue = color1 &0xff;
          color = red << 16 | green << 8 | blue;
          red = *(temp_sprite + 2) & 0xff;
          green = *(temp_sprite + 1) & 0xff;
          blue = *(temp_sprite) &0xff;
          color2 = red << 16 | green << 8 | blue;
          if (xpm_transparency_color(type) != color2) {
            vg_draw_pixel(sprite.x + j, sprite.y + i, color1);
          }
          temp_sprite += 3;
        }
      }
      break;
    case (4):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          byte1 = color1 & 0xff000000;
          red = color1 & 0xff0000;
          green = color1 & 0xff00;
          blue = color1 &0xff;
          color = byte1 << 24 | red << 16 | green << 8 | blue;
          byte1 = *(temp_sprite + 3) & 0xff;
          red = *(temp_sprite + 2) & 0xff;
          green = *(temp_sprite + 1) & 0xff;
          blue = *(temp_sprite) &0xff;
          color2 = byte1 << 24 | red << 16 | green << 8 | blue;
          if (xpm_transparency_color(type) != color2) {
            vg_draw_pixel(sprite.x + j, sprite.y + i, color1);
          }
          temp_sprite += 4;
        }
      }
      break;
    default:
      break;
  }
}

void(erase_sprite)(struct Sprite sprite){

 uint32_t color, red, green, blue, byte1, byte2;
 uint8_t * temp_sprite = sprite.sprite1;
 switch ((vmi_p.BitsPerPixel + 7) / 8) {
    case (1):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          if(xpm_transparency_color(type) != *(temp_sprite)){
            vg_draw_pixel(sprite.x + j, sprite.y + i, 0);
          }
          temp_sprite++;
        }
      }
      break;
    case (2):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          if (vmi_p.BitsPerPixel == 15) {
            byte1 = *(temp_sprite + 1) & 0xef;
          }
          else
          byte1 = *(temp_sprite + 1) & 0xff;
          byte2 = *(temp_sprite) &0xff;
          color = byte1 << 8 | byte2;
          if(xpm_transparency_color(type) != color){
            vg_draw_pixel(sprite.x + j, sprite.y + i, 0);
          }
          temp_sprite += 2;
        }
      }
      break;
    case (3):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          red = *(temp_sprite + 2) & 0xff;
          green = *(temp_sprite + 1) & 0xff;
          blue = *(temp_sprite) &0xff;
          color = red << 16 | green << 8 | blue;
          if(xpm_transparency_color(type) != color){
            vg_draw_pixel(sprite.x + j, sprite.y + i, 0);
          }
          temp_sprite += 3;
        }
      }
      break;
    case (4):
      for (int i = 0; i < sprite.height; i++) {
        for (int j = 0; j < sprite.width; j++) {
          byte1 = *(temp_sprite + 3) & 0xff;
          red = *(temp_sprite + 2) & 0xff;
          green = *(temp_sprite + 1) & 0xff;
          blue = *(temp_sprite) & 0xff;
          color = byte1 << 24 | red << 16 | green << 8 | blue;
          if(xpm_transparency_color(type) != color){
            vg_draw_pixel(sprite.x + j, sprite.y + i, 0);
          }
          temp_sprite += 4;
        }
      }
      break;
    default:
      break;
  }
}

void(load_sprites)(uint16_t mode) {
  switch (mode) {
    case 0x115:
      type = XPM_8_8_8;
      load_mode_0x115();
      break;
    case 0x110:
      type = XPM_1_5_5_5;
      load_mode_0x110();
      break;
    case 0x11A:
      type = XPM_5_6_5;
      load_mode_0x11A();
      break;
    case 0x14C:
      type = XPM_8_8_8_8;
      load_mode_0x14C();
      break;
  }
}

int (vbe_get_mode_info_custom)(uint16_t mode, vbe_mode_info_t *vmi_p){
  
  mmap_t map;
  if(lm_alloc(sizeof(vbe_mode_info_t),&map) == NULL){
    return 1;
  }

  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ax = 0x4F01; // VBE call, function 01 -- read VBE mode
  reg86.es = PB2BASE(map.phys);
  reg86.di = PB2OFF(map.phys);
  reg86.cx = mode;
  if( sys_int86(&reg86) != OK ) {
    printf("vg_exit(): sys_int86() failed /n");
    return 1;
  }    
  *vmi_p = *((vbe_mode_info_t*) map.virt);
 
  if(!lm_free(&map)){
    return 1;
  }
  return 0;
}
