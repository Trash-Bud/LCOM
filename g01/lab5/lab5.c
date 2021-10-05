#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include "video_gr.h"
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "i8042.h"
#include "keyboard.h"
#include "timer.h"

extern int counter;
extern uint8_t scancode;
extern vbe_mode_info_t vmi_p;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if (vg_init(mode) == NULL){
    return 1;
  }
  sleep(delay);
  vg_exit();

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  uint8_t bit_no = IRQ1;
  uint32_t irq_set = BIT(bit_no);
  kbc_subscribe();
  int ipc_status;
  message msg;
  double r = 0;
  vg_init(mode);
  vg_draw_rectangle(x, y, width, height, color); //draws to the buffer

  double_buffer();
  while (scancode != ESCAPE) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            kbc_ih();
          }
          break;
        default: break;
      }
    }
  }
  kbc_unsubscribe();
  vg_exit();
  return 1;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  vg_init(mode);
  int ipc_status;
  message msg;
  double r = 0;
  int color;
  uint32_t R_first;
  uint32_t G_first;
  uint32_t B_first;
  switch (mode) {
    case 0x105:
      break;
    case 0x110:
      R_first = (first & 0x00007C00) >> vmi_p.RedFieldPosition;
      G_first = (first & 0x000003E0) >> vmi_p.GreenFieldPosition;
      B_first = (first & 0x0000001F) >> vmi_p.BlueFieldPosition;

    case 0x115:
      R_first = (first & 0x00FF0000) >> vmi_p.RedFieldPosition;
      G_first = (first & 0x0000FF00) >> vmi_p.GreenFieldPosition;
      B_first = (first & 0x000000FF) >> vmi_p.BlueFieldPosition;

      break;
    case 0x11A:
      R_first = (first & 0x0000F800) >> vmi_p.RedFieldPosition;
      G_first = (first & 0x000007E0) >> vmi_p.GreenFieldPosition;
      B_first = (first & 0x0000001F) >> vmi_p.BlueFieldPosition;
      break;
    case 0x14C:
      R_first = (first & 0x00FF0000) >> vmi_p.RedFieldPosition;
      G_first = (first & 0x0000FF00) >> vmi_p.GreenFieldPosition;
      B_first = (first & 0x000000FF) >> vmi_p.BlueFieldPosition;
      break;
  }

  int R, G, B;
  int x_rectangles = vmi_p.XResolution / no_rectangles;
  int y_rectangles = vmi_p.YResolution / no_rectangles;

  uint8_t bit_no = IRQ1;
  uint32_t irq_set = BIT(bit_no);
  kbc_subscribe();

  for(int i = 0; i < no_rectangles; i++){ // Linhas
    for(int j = 0; j < no_rectangles; j++){ //colunas
      switch (mode) {
        case 0x105:
          color = (first + (i * no_rectangles + j) * step) % (1 << vmi_p.BitsPerPixel);
          break;
        default:
          R = (R_first + j * step) % (1 << vmi_p.RedMaskSize);
          G = (G_first + i * step) % (1 << vmi_p.GreenMaskSize);
          B = (B_first + (j + i) * step) % (1 << vmi_p.BlueMaskSize);

          color = 0 | (R << vmi_p.RedFieldPosition) | (G << vmi_p.GreenFieldPosition) | (B << vmi_p.BlueFieldPosition);
          break;
    }

    vg_draw_rectangle(j * x_rectangles, i * y_rectangles, x_rectangles, y_rectangles, color);
    }
     if (i * y_rectangles > vmi_p.YResolution) {
      break;
    }
  }
    
  double_buffer();
  while (scancode != ESCAPE) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            kbc_ih();
          }
          break;
        default: break;
      }
    }
  }
  kbc_unsubscribe();

  vg_exit();

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  int ipc_status;
  message msg;
  double r = 0;
  uint8_t bit_no = IRQ1;
  uint32_t irq_set = BIT(bit_no);
  kbc_subscribe();

  int mode = 0x105;
  vg_init(mode);
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *sprite = xpm_load(xpm, type, &img);
  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      vg_draw_pixel(x + j, i + y, *(sprite));
      sprite++;
    }
  }
  double_buffer();

  while (scancode != ESCAPE) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            kbc_ih();
          }
          break;
        default: break;
      }
    }
  }

  kbc_unsubscribe();
  vg_exit();
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {

  //set frequency
  timer_set_frequency(0,fr_rate);
  bool done_with_moving = false;
  int ipc_status;
  message msg;
  double r = 0;
  uint8_t bit_no_kbd = IRQ1;
  uint8_t bit_no_timer = IRQ0;
  uint32_t irq_set_kbd = BIT(bit_no_kbd);
  uint32_t irq_set_timer = BIT(bit_no_timer);
  kbc_subscribe();
  timer_subscribe_int(&bit_no_timer);

  int mode = 0x105;
  vg_init(mode);
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t *sprite = xpm_load(xpm, type, &img);
  draw_sprite(img, sprite, xi, yi);

  double_buffer();

  while (scancode != ESCAPE) { //critério ESC
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                                 /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set_kbd) { /* subscribed interrupt */
            kbc_ih();
          }
          if (msg.m_notify.interrupts & irq_set_timer) { /* subscribed interrupt */
            timer_int_handler();
            if (!done_with_moving) {
                //mover a sprite com speed adequado
                if(speed < 0 && counter % (-speed) == 0){
                    if (xi == xf) {
                    vg_draw_rectangle(xi, yi, img.width, img.height, 0);
                    yi = yi + 1;
                    if (yi > yf) {
                      yi = yf;
                    }
                    draw_sprite(img, sprite, xi, yi);
                    if (yi == yf)
                      done_with_moving = true;
                  }
                  else if (yi == yf) {
                    vg_draw_rectangle(xi, yi, img.width, img.height, 0);
                    xi = xi + 1;
                    if (xi > xf) {
                      xi = xf;
                    }
                    draw_sprite(img, sprite, xi, yi);
                    if (xi == xf)
                      done_with_moving = true;
                  }
                }
                else if(speed > 0){
                  if (xi == xf) {
                  vg_draw_rectangle(xi, yi, img.width, img.height, 0);
                  yi = yi + speed;
                  if (yi > yf) {
                    yi = yf;
                  }
                  draw_sprite(img, sprite, xi, yi);
                  if (yi == yf)
                    done_with_moving = true;
                }
                else if (yi == yf) {
                  vg_draw_rectangle(xi, yi, img.width, img.height, 0);
                  xi = xi + speed;
                  if (xi > xf) {
                    xi = xf;
                  }
                  draw_sprite(img, sprite, xi, yi);
                  if (xi == xf)
                    done_with_moving = true;
                }
              }
                
              double_buffer();
            }
          }
      
      break;
      default: break;
    }
  }
}

kbc_unsubscribe();
timer_unsubscribe_int();
vg_exit();

return 0;
}

int(video_test_controller)() {
  //para implementar ainda
  /*
  int r;

  struct minix_mem_range mr;
  mr.mr_base = (phys_bytes) BASE_ADDRESS;	
  mr.mr_limit = mr.mr_base + MiB;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
     panic("sys_privctl (ADD_MEM) failed: %d\n", r);
  }
   
  mmap_t map;
  if(lm_alloc(sizeof(vbe_mode_info_t),&map) == NULL){
    return 1;
  }

  char* vbe_signature = map.virt;

	// VBE_CONTROLLER_SIGNATURE_VBE2 = 0x0200
	vbe_signature[0] = 'V';
	vbe_signature[1] = 'B';
	vbe_signature[2] = 'E';
	vbe_signature[3] = '2';

  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ax = 0x4F00; // VBE call, function 00 -- read VBE controler info
  reg86.bx = 1 << 14; //set bit 14: linear framebuffer
  reg86.es = PB2BASE(map.phys);
  reg86.di = PB2OFF(map.phys);

  if( sys_int86(&reg86) != OK ) {
    printf("vg_exit(): sys_int86() failed \n");
    return 1;
  }    

  vg_vbe_contr_info_t info_p = *((vg_vbe_contr_info_t*) map.virt);
 
  if(!lm_free(&map)){
    return 1;
  }

   vg_display_vbe_contr_info(&info_p);
   return 1; */
   return 1;
}
