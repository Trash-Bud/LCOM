// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <lcom/timer.h>
#include <stdlib.h>
#include <time.h>

#include <stdbool.h>
#include <stdint.h>
// Any header files included below this line should have been created by you
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "logic.h"
#include "mouse.h"
//#include "rtc.h"
#include "video_gr.h"
#include "power_up.h"

extern vbe_mode_info_t vmi_p;
extern int counter;
extern uint8_t scancode;
extern struct Sprite mouse;
extern struct Player player1, player2;
extern struct Ball ball_;
/// <summary>
/// sprite saying 'score'
/// </summary>
struct Sprite score;
extern bool reading_error;
extern struct packet packet1;
/// <summary>
/// True if the user is in the menu, false otherwise
/// </summary>
bool in_menu = true;
extern struct Sprite MainMenuSprites[7];
extern struct Sprite ResolutionsMenu[7];
extern struct Sprite GameTypeTimeLimit[4];
extern struct Sprite GameTypePointLimit[4];
extern struct Sprite GameType[4];
extern struct Sprite PauseScreen[4];
extern struct Sprite WinScreen[7];
extern struct Sprite HighScores[4];
/// <summary>
/// array containing all the sprites of the current menu
/// </summary>
struct Sprite CurrentMenu[8];
extern int size_menu;
/// <summary>
/// current video mode
/// </summary>
uint16_t mode_;
extern struct Sprite big_numbers_and_letters[36];
extern struct Sprite small_numbers[12];
/// <summary>
/// flag which checks where and what the player is writtig
/// </summary>
bool writingToPointLimit;
/// <summary>
/// flag which checks where and what the player is writtig
/// </summary>
bool writingToTimeLimit;
/// <summary>
/// flag which checks where and what the player is writtig
/// </summary>
bool writingName;
/// <summary>
/// Time limit of a game with a time limit
/// </summary>
int max_time = 0;
/// <summary>
/// Point limit of a game with a point limit
/// </summary>
int point_limit = 0;
int character_number = 0;
extern int highest_score;
///<summary>
/// 0 - endless, 1 - timed , 2 - points_max
///</summary>
int game_type = 0;
extern char highest_score_name[25];
extern int size_of_highscore_name;
extern int counter_timer;
/// <summary>
/// array with the name of the person who did the highest score
/// </summary>
char name[25];
extern struct PowerUp Power_ups[3];
/// <summary>
/// True if in game
/// </summary>
bool inGame = true;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

static int print_usage() {
  printf("Usage: <mode - hex>\n");
  return 1;
}

/// <summary>
/// Mane game loop
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int(proj_main_loop)(int argc, char *argv[]) {
  srand(time(NULL));
  mode_ = 0x14C;
  vg_init(mode_);
  initialize_powerUps();
  read_highscore_from_file();
  //subscribe timer interrupts
  uint8_t bit_no = TIMER0_IRQ;
  uint32_t irq_set_timer = BIT(bit_no);
  timer_subscribe_int(&bit_no);

  //subscribe mouse interrupts

  if (enable_mouse_data() != 0)
    return 1;
  uint8_t bit_no_mouse = 2;
  uint32_t irq_set_mouse = BIT(bit_no_mouse);
  kbc_subscribe();

  //simulate a mouse 

  //set frequency to 60Hz
  timer_set_frequency(0, 60);

  //subscribe keyboard interrupts
  uint8_t bit_no_kbd = IRQ1;
  uint32_t irq_set_kbd = BIT(bit_no_kbd);
  kbd_subscribe();

  //subscribe rtc interrupts

  rtc_enable_update();
  uint8_t bit_no_rtc = 3;
  uint32_t irq_set_rtc = BIT(bit_no_rtc);
  rtc_subscribe();


  load_sprites(mode_);
  int ipc_status;
  message msg;
  int r = 0;
  int waiting_frames = 0;
  int PowerUpOnScreen = -1;

  reset_ball();
  create_mouse();

  initialize_players();

  // display ball_ in center of screen

  copyArray(MainMenuSprites,7);
  draw_menu_buttons(CurrentMenu,mode_);

  double_buffer();

  while (inGame) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_timer) { /* subscribed interrupt */
            timer_int_handler();
            if (!in_menu){
            
              if(game_type == 1){
                vg_draw_rectangle(vmi_p.XResolution / 2 + score.width / 2 + 80 - small_numbers[3].width * 3, 1, small_numbers[3].width * 4 + 1, small_numbers[3].height, 0);
                write_small_number_to_screen(max_time, vmi_p.XResolution / 2 + score.width / 2 + 80, 1, 0xffffff);
                if(counter_timer % 60 == 0){
                  max_time--;
                }
              
                if(max_time == 0){
                  copyArray(WinScreen,8);
                  in_menu = true;
                 }
              }
              if(game_type == 2 && (player1.score == point_limit || player2.score == point_limit)){
                copyArray(WinScreen,8);
                in_menu = true;
              }

                
              //handle spawning new power ups
              if(PowerUpOnScreen == -1){
                PowerUpOnScreen = handlePowerUpSpawn();
              }else{
                handle_animation(&Power_ups[PowerUpOnScreen].animation,10,false);
                if(is_ball_colliding_with_powerUp(&Power_ups[PowerUpOnScreen])){
                    collect_power_up(&Power_ups[PowerUpOnScreen]);
                    PowerUpOnScreen = -1;
                }
              }
              handleRemovePowerUp();

              control_player2();
              
              
              control_player1();
            
              
              if (!overlap_save_p1() && !overlap_save_p2()) {
                erase_sprite(ball_.sprite);
              }
              

              //scancode = q, pause menu pops up
              checkIfPaused();

              //Changing the position of the ball
              handle_ball_movement(&waiting_frames);

              
              overlap_save_p1();
              overlap_save_p2();
              

              draw_sprite(ball_.sprite);
              draw_sprite(player1.sprite[player1.current_sprite]);
              draw_sprite(player2.sprite[player2.current_sprite]);
            }
            else { //if in menu
              if(counter == 0){
                mouse_movement();

                if (packet1.lb) {
                  handle_menu_events(CurrentMenu, size_menu);
                  if (!in_menu) {
                    erase_sprite(mouse);
                    vg_draw_rectangle(0, 0, vmi_p.XResolution, vmi_p.YResolution, 0);
                    update_score();
                    vg_draw_hline(0, score.height + score.y + 2, vmi_p.XResolution, 0xffffff);
                    draw_sprite(score);
                    if (!checkIfEqual(CurrentMenu,PauseScreen,4)) {
                      deactivate_all_power_up();
                      PowerUpOnScreen = -1;
                    }
              
                    continue;
                  }
                  packet1.lb = false;
                }
                draw_menu_buttons(CurrentMenu,mode_);
                handleHoverMenu(CurrentMenu, size_menu);
                draw_sprite(mouse);
              } 
              realTimeWritting();
            }
            double_buffer();
          }
          if (msg.m_notify.interrupts & irq_set_kbd) { /* subscribed interrupt */
            kbd_ih();
        
          }
          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();
            
            if (reading_error && counter != 0) {
              
            }
            else if (reading_error && counter == 0) {
            
              reading_error = false;
            }
            else {
              assemble_mouse_packet();
            }
          }
          if (msg.m_notify.interrupts & irq_set_rtc) {
            rtc_ih();
          }
          
          break;
        default:
          break;
      }
    }
  }

  empty_buffer();

  timer_unsubscribe_int();
  kbd_unsubscribe();
  kbc_unsubscribe();


  rtc_unsubscribe();

  rtc_disable_update();


  if (disable_mouse_data() != 0) return 1;
  vg_exit();

  bool const minix3_logo = true;
  bool const grayscale = false;
  uint8_t const delay = 5;
  uint16_t mode;

  if (argc != 1)
    return print_usage();

  // parse mode info (it has some limitations for the sake of simplicity)

  if (sscanf(argv[0], "%hx", &mode) != 1) {
    printf("%s: invalid mode (%s)\n", __func__, argv[0]);

    return print_usage();
  }

  return proj_demo(mode, minix3_logo, grayscale, delay);
}
