#include <lcom/lcf.h>
#include <stdlib.h>
#include "power_up.h"
#include "video_gr.h"

/// <summary>
/// Array of the tree existing power ups
/// </summary>
struct PowerUp Power_ups[3];
extern int counter_timer;
extern vbe_mode_info_t vmi_p;
extern struct Player player1, player2;
extern struct Ball ball_;
/// <summary>
/// Constant of the duration of a power up
/// </summary>
const int POWERUP_DURATION = 7;
extern struct Sprite score;

void initialize_powerUps(){
    Power_ups[0].func = ball_speed_power_up_function;
    Power_ups[0].active = false;
    Power_ups[0].render = false;
    Power_ups[1].func = increase_player_size_power_up_function;
    Power_ups[1].active = false;
    Power_ups[1].render = false;
    Power_ups[2].func = decrease_player_size_power_up_function;
    Power_ups[2].active = false;
    Power_ups[2].render = false;
}

int handlePowerUpSpawn(){
    int roll = rand() % 3;
    if(roll == 0){
      int powerUpIndex = rand() % 3;
      Power_ups[powerUpIndex].render = true;
      int x = rand() % (vmi_p.XResolution - player2.sprite[0].width - 40);
      int y = rand() % (vmi_p.YResolution - player2.sprite[0].width - 30 );
      if(x < player2.sprite[0].width + 30) x = player2.sprite[0].width + 30;
      if (y < score.height + score.y + 3) y = score.height + score.y + 3;
      for(int i = 0;i < Power_ups[powerUpIndex].animation.number_of_frames;i++){
          Power_ups[powerUpIndex].animation.frames[i].x =  x;
          Power_ups[powerUpIndex].animation.frames[i].y =  y;
          set_animation_initial_frame(&Power_ups[powerUpIndex].animation, counter_timer);
      }
      return powerUpIndex;
    }
    return -1;
}

void deactivate_all_power_up() {
  for (int i = 0; i < 3; i++) {
    Power_ups[i].render = false;
    Power_ups[i].active = false;
  }
}

void ball_speed_power_up_function(){
    ball_.ball_speed = 14;
}

void increase_player_size_power_up_function(){
    if(ball_.x_speed > 0){
        //it was player 1 who last touched the ball, so he gets the powerup
        erase_sprite(player1.sprite[player1.current_sprite]);
        player1.sprite[2].x = player1.sprite[player1.current_sprite].x;
        player1.current_sprite = 2;
        
    }else{
        //player 2 gets enlarged
       erase_sprite(player2.sprite[player2.current_sprite]);
       player2.sprite[2].x = player2.sprite[player2.current_sprite].x;
       player2.current_sprite = 2;
    }
}


void decrease_player_size_power_up_function(){
    if(ball_.x_speed > 0){
        //it was player 1 who last touched the ball, so player 2 gets decreased
        erase_sprite(player2.sprite[player2.current_sprite]);
        player2.sprite[1].x = player2.sprite[player2.current_sprite].x;
        player2.current_sprite = 1;
        
    }else{
        //player 1 gets decreased
        erase_sprite(player1.sprite[player1.current_sprite]);
        player1.sprite[1].x = player1.sprite[player1.current_sprite].x;
        player1.current_sprite = 1;

    }
}

void handleRemovePowerUp(){
    for(int i = 0; i < 3; i++){
        if(Power_ups[i].active){
            if( (counter_timer - Power_ups[i].counter_initial)/ 60 >= POWERUP_DURATION ){
                Power_ups[i].active = false;
                switch(i){
                    case 0:
                        ball_.ball_speed = 7;
                        break;
                    case 1:
                        if(player1.current_sprite == 2){
                            erase_sprite(player1.sprite[player1.current_sprite]);
                            player1.current_sprite = 0;
                            player1.sprite[player1.current_sprite].x = player1.sprite[2].x;
                        }else if(player2.current_sprite == 2){
                            erase_sprite(player2.sprite[player2.current_sprite]);
                            player2.current_sprite = 0;
                            player2.sprite[player2.current_sprite].x = player2.sprite[2].x;
                        }
                        break;
                    case 2:
                       if(player1.current_sprite == 1){
                            erase_sprite(player1.sprite[player1.current_sprite]);
                            player1.current_sprite = 0;
                            player1.sprite[player1.current_sprite].x = player1.sprite[1].x;
                        }else if(player2.current_sprite == 1){
                            erase_sprite(player2.sprite[player2.current_sprite]);
                            player2.current_sprite = 0;
                            player2.sprite[player2.current_sprite].x = player2.sprite[1].x;
                        }
                        break; 
                }
            }
        }
    }
}



void collect_power_up(struct PowerUp* power_up){
    power_up->active = true;
    power_up->render = false;
    power_up->counter_initial = counter_timer;
    erase_sprite(power_up->animation.frames[power_up->animation.current_frame]);
    erase_sprite(ball_.sprite);
    draw_sprite(ball_.sprite);
    power_up->func();
}

bool is_ball_colliding_with_powerUp(struct PowerUp* power_up){
    int anim_x = power_up->animation.frames[power_up->animation.current_frame].x;
    int anim_width = power_up->animation.frames[power_up->animation.current_frame].width;
    int anim_y = power_up->animation.frames[power_up->animation.current_frame].y;
    int anim_height = power_up->animation.frames[power_up->animation.current_frame].height;
    for (int x = anim_x; x <= anim_x + anim_width; x++) {
    for (int y = anim_y; y <= anim_y + anim_height; y++) {
      if (is_colliding(x, y)) {
        return true;
      }
    }
  }
  return false;
}
