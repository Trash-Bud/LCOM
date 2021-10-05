#include "video_gr.h"
#include "logic.h"
#include "power_up.h"
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include "i8042.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/// <summary>
/// mathematical constant for PI
/// </summary>
#define PI 3.14159265

extern uint8_t scancode;
extern bool inGame;
/// <summary>
/// players
/// </summary>
struct Player player1, player2;
/// <summary>
/// ball
/// </summary>
struct Ball ball_;
extern struct Sprite big_numbers_and_letters[36];
extern struct Sprite small_numbers[12];
extern struct Sprite score;
/// <summary>
/// cursor
/// </summary>
struct Sprite mouse;
extern vbe_mode_info_t vmi_p;
extern struct Sprite CurrentMenu[8];
extern struct Sprite MainMenuSprites[7];
extern struct Sprite ResolutionsMenu[7];
extern struct Sprite GameTypeTimeLimit[4];
extern struct Sprite GameTypePointLimit[4];
extern struct Sprite GameType[4];
extern struct Sprite PauseScreen[4];
extern struct Sprite WinScreen[8];
extern struct Sprite HighScores[5];
extern struct Sprite HoverButtons[16];
/// <summary>
/// true if the player is playing localy, false otherwise (remote games to implemented)
/// </summary>
bool local = true;
extern bool in_menu;
extern uint16_t mode_;
extern bool writingToPointLimit, writingToTimeLimit, writingName; 
extern int max_time;
extern int character_number;
extern int size_menu;
extern int point_limit;
/// <summary>
/// highest_score value
/// </summary>
int highest_score = 2;
/// <summary>
/// name of the person with the highest score
/// </summary>
char highest_score_name[25] = "MIGUEL";
/// <summary>
/// size of th mentioned name
/// </summary>
int size_of_highscore_name = 6;
extern int game_type;
extern char name[25];
extern struct Date date;
extern int counter;
extern struct packet packet1;
extern struct PowerUp Power_ups[3];


void checkIfPaused(){
  if (scancode == 0x10) {
      in_menu = true;
      vg_draw_rectangle(0, 0, vmi_p.XResolution, vmi_p.YResolution, 0xffffff);
      copyArray(PauseScreen, 4);
      draw_menu_buttons(CurrentMenu,mode_);
      double_buffer();
  }
}

void handle_ball_movement(int* waiting_frames){
 
 if (ball_.sprite.x >= vmi_p.XResolution - ball_.sprite.width) {
      player1.score++;
   if (ball_.sprite.y < score.height + score.y + 3) {
        ball_.sprite.y = score.height + score.y + 3;
      }
      erase_sprite(ball_.sprite);
      reset_ball();
      update_score();
    }
    else if (ball_.sprite.x <= 0) {
      player2.score++;
      if (ball_.sprite.y < score.height + score.y + 3) {
        ball_.sprite.y = score.height + score.y + 3;
      }
      erase_sprite(ball_.sprite);
      reset_ball();
      update_score();
    }
    else if (ball_.sprite.y == vmi_p.YResolution - ball_.sprite.height || ball_.sprite.y == score.height + score.y + 3) {
      ball_.x_speed = ball_.x_speed;
      ball_.y_speed = -ball_.y_speed;
    }
    else if ((*waiting_frames) == 0) {
      if (colision(&player1) || colision(&player2)) {
        printf("Collided!\n");
        (*waiting_frames) = 5;
      }
    }
    else {
      (*waiting_frames)--;
    }

    ball_.sprite.x = ball_.sprite.x + ball_.x_speed;
    ball_.sprite.y = ball_.sprite.y + ball_.y_speed;

    if (ball_.sprite.x > vmi_p.XResolution - ball_.sprite.width) {
      ball_.sprite.x = vmi_p.XResolution - ball_.sprite.width;
    }
    else if (ball_.sprite.x < 0) {
      ball_.sprite.x = 0;
    }
    else if (ball_.sprite.y > vmi_p.YResolution - ball_.sprite.height){
      ball_.sprite.y = vmi_p.YResolution - ball_.sprite.height;
    } 
    else if (ball_.sprite.y < score.height + score.y + 3) {
      ball_.sprite.y = score.height + score.y + 3;
    }

}

void read_highscore_from_file(){
  FILE* fp;
  char line[32];
  fp = fopen("/home/lcom/labs/proj/highscores.txt","r");
  if(fp ==NULL){
    exit(0);
  }
  printf("Opened file! \n");
  fgets(line,32,(FILE*)fp);
  
  int i = 0;
  while(line[i] != '\r' && line[i] != '\n' && line[i] != '\0' && line[i] != ' '){
    highest_score_name[i] = line[i];
    i++;
  }
  printf("highest score name: %s\n", highest_score_name);
  size_of_highscore_name = i;

  fgets(line,32,(FILE*)fp);
  printf("line: %s\n", line);
  highest_score = atoi(line);
  printf("highest score: %d\n", highest_score);


  fgets(line,32,(FILE*)fp);
  date.day = atoi(line);

  fgets(line,32,(FILE*)fp);
  date.month = atoi(line);

  fgets(line,32,(FILE*)fp);
  date.year = atoi(line);

  fgets(line,32,(FILE*)fp);
  date.hour = atoi(line);

  fgets(line,32,(FILE*)fp);
  date.minute = atoi(line);

  fgets(line,32,(FILE*)fp);
  date.second = atoi(line);
  fclose(fp);
 
}

void write_highscore_to_file(){
  FILE* fp;
  fp = fopen("/home/lcom/labs/proj/highscores.txt","w+");
  for(int i = 0; i < size_of_highscore_name; i++){
    fprintf(fp, "%c", highest_score_name[i]);
  }
  fprintf(fp, "               ");
  fprintf(fp,"\n");
  fprintf(fp,"%d\n",highest_score);
  fprintf(fp, "%02X\n%02X\n%02X\n%02X\n%02X\n%02X\n", date.day, date.month,date.year, date.hour, date.minute, date.second);
  fclose(fp);
}

void copyArray(struct Sprite A[], unsigned int size){
  for(unsigned int i = 0; i < size ; i++){
    CurrentMenu[i] = A[i];
  }
  size_menu = size;
}

void initialize_players(){
  for(int i = 0; i < 3; i++){
    player1.sprite[i].y = 40;
    player1.sprite[i].x = 20;
    player2.sprite[i].x = vmi_p.XResolution - 20 - player2.sprite[i].width;
    player2.sprite[i].y = vmi_p.YResolution - player2.sprite[i].height - 20;
  }

  player1.y_speed = 20;
  player1.score = 0;

  player2.score = 0;
  player2.y_speed = 20;
}

void handleHoverMenu(struct Sprite A[], unsigned int size){
  int clickedButton = ButtonClicked(A,size);
  
  if(clickedButton == -1){
    return;
  } 
  else if(checkIfEqual(A,MainMenuSprites,7)){
    switch(clickedButton){
      case 0:
        return;
      case 1:
        HoverButtons[6].x = MainMenuSprites[1].x;
        HoverButtons[6].y = MainMenuSprites[1].y;
        draw_sprite(HoverButtons[6]);
        return;
      case 2:
        HoverButtons[7].x = MainMenuSprites[2].x;
        HoverButtons[7].y = MainMenuSprites[2].y;
        draw_sprite(HoverButtons[7]);
        return;
      case 3:
        HoverButtons[8].x = MainMenuSprites[3].x;
        HoverButtons[8].y = MainMenuSprites[3].y;
        draw_sprite(HoverButtons[8]);
        return;
      case 4:
        HoverButtons[9].x = MainMenuSprites[4].x;
        HoverButtons[9].y = MainMenuSprites[4].y;
        draw_sprite(HoverButtons[9]);
        
        return;
      case 5:
        HoverButtons[10].x = MainMenuSprites[5].x;
        HoverButtons[10].y = MainMenuSprites[5].y;
        draw_sprite(HoverButtons[10]);
      
        return;
      case 6:
        HoverButtons[13].x = MainMenuSprites[6].x;
        HoverButtons[13].y = MainMenuSprites[6].y;
        draw_sprite(HoverButtons[13]);
        return;

    }
  }
else if(checkIfEqual(A,ResolutionsMenu,6)){
  switch(clickedButton){
    case 0:
      HoverButtons[2].x = ResolutionsMenu[0].x;
      HoverButtons[2].y = ResolutionsMenu[0].y;
      draw_sprite(HoverButtons[2]);
      return;
    case 1:
      HoverButtons[3].x = ResolutionsMenu[1].x;
      HoverButtons[3].y = ResolutionsMenu[1].y;
      draw_sprite(HoverButtons[3]);
      return;
    case 2:
      HoverButtons[0].x = ResolutionsMenu[2].x;
      HoverButtons[0].y = ResolutionsMenu[2].y;
      draw_sprite(HoverButtons[0]);
      return;
    case 3:
      HoverButtons[1].x = ResolutionsMenu[3].x;
      HoverButtons[1].y = ResolutionsMenu[3].y;
      draw_sprite(HoverButtons[1]);
      return;
    case 4:
      HoverButtons[4].x = ResolutionsMenu[4].x;
      HoverButtons[4].y = ResolutionsMenu[4].y;
      draw_sprite(HoverButtons[4]);
      return;
    case 5:
      return;
  }
}
else if(checkIfEqual(A,GameTypeTimeLimit,4)){
  switch(clickedButton){
    case 0:
      return;
    case 1:
      HoverButtons[4].x = GameTypeTimeLimit[1].x;
      HoverButtons[4].y = GameTypeTimeLimit[1].y;
      draw_sprite(HoverButtons[4]);
      return;
    case 2:
      return;
    case 3:
      return;
  }

}else if(checkIfEqual(A,GameTypePointLimit,4)){
  switch(clickedButton){
    case 0:
      return;
    case 1:
      HoverButtons[4].x = GameTypePointLimit[1].x;
      HoverButtons[4].y = GameTypePointLimit[1].y;
      draw_sprite(HoverButtons[4]);
      return;
    case 2:
      return;
    case 3:
      return;
  }
}
else if(checkIfEqual(A,GameType,4)){
  switch(clickedButton){
    case 0:
      HoverButtons[14].x = GameType[0].x;
      HoverButtons[14].y = GameType[0].y;
      draw_sprite(HoverButtons[14]);
      return;
    case 1:
      HoverButtons[5].x = GameType[1].x;
      HoverButtons[5].y = GameType[1].y;
      draw_sprite(HoverButtons[5]);
      return;
    case 2:
      return;
    case 3:
      HoverButtons[11].x = GameType[3].x;
      HoverButtons[11].y = GameType[3].y;
      draw_sprite(HoverButtons[11]);
      return;
  }
}
else if(checkIfEqual(A,PauseScreen,4)){
  switch(clickedButton){
    case 0:
      HoverButtons[15].x = PauseScreen[0].x;
      HoverButtons[15].y = PauseScreen[0].y;
      draw_sprite(HoverButtons[15]);
      return;
    case 1:
      return;
    case 2:
      HoverButtons[12].x = PauseScreen[2].x;
      HoverButtons[12].y = PauseScreen[2].y;
      draw_sprite(HoverButtons[12]);
      return;
    case 3:
      return;
    
  }
}
else if(checkIfEqual(A,WinScreen,8)){
  switch(clickedButton){
    case 0:
      return;
    case 1:
      return;
    case 2:
      
      return;
    case 3:
      
      return;
    case 4:
      
      return;
    case 5:
      HoverButtons[12].x = WinScreen[5].x;
      HoverButtons[12].y = WinScreen[5].y;
      draw_sprite(HoverButtons[12]);
      return;
    case 6:
      HoverButtons[12].x = WinScreen[6].x;
      HoverButtons[12].y = WinScreen[6].y;
      draw_sprite(HoverButtons[12]);
      return;
    case 7:
      return;
  }
}
else if(checkIfEqual(A,HighScores,5)){
   switch (clickedButton)
   {
   case 4:
      HoverButtons[4].x = HighScores[4].x;
      HoverButtons[4].y = HighScores[4].y;
      draw_sprite(HoverButtons[4]);
      return;
   
   default:
     return;
   }
  }

}

void handle_menu_events(struct Sprite A[], unsigned int size){
  int clickedButton = ButtonClicked(A,size);
  if(clickedButton == -1) return;
  else if(checkIfEqual(A,MainMenuSprites,7)){
    switch(clickedButton){
      case 0:
        return;
      case 1:
        inGame = false;
        return;
      case 2:
        return;
      case 3:
        copyArray(HighScores,5);
        return;
      case 4:
        local = true;
        copyArray(GameType,4);
        return;
      case 5:
        copyArray(ResolutionsMenu,6);
        return;
      case 6:
        local = false;
        return;

    }
  }
else if(checkIfEqual(A,ResolutionsMenu,6)){
  switch(clickedButton){
    case 0:
      vg_exit();
      mode_ = 0x110;
      vg_init(mode_);
      load_sprites(mode_);
      copyArray(MainMenuSprites, 7);
      reset_ball();
      create_mouse();

      initialize_players();
      return;
    case 1:
      vg_exit();
      mode_ = 0x115;
      vg_init(mode_);
      load_sprites(mode_);
      copyArray(MainMenuSprites, 7);
      reset_ball();
      create_mouse();

      initialize_players();
      return;
    case 2:
      vg_exit();
      mode_ = 0x14c;
      vg_init(mode_);
      load_sprites(mode_);
      copyArray(MainMenuSprites, 7);
      reset_ball();
      create_mouse();

      initialize_players();
      return;
    case 3:
      vg_exit();
      mode_ = 0x11a;
      vg_init(mode_);
      load_sprites(mode_);
      copyArray(MainMenuSprites, 7);
      reset_ball();
      create_mouse();

      initialize_players();
      return;
    case 4:
      copyArray(MainMenuSprites,7);
      return;
    case 5:
      return;
  }
}
else if(checkIfEqual(A,GameTypeTimeLimit,4)){
  switch(clickedButton){
    case 0:
      return;
    case 1:
      in_menu = false;
      character_number = 0;
      writingToTimeLimit = false;
      character_number = 0;
      return;
    case 2:
      writingToTimeLimit = true;
      return;
    case 3:
      return;
  }

}else if(checkIfEqual(A,GameTypePointLimit,4)){
  switch(clickedButton){
    case 0:
      return;
    case 1:
      in_menu = false;
      character_number = 0;
      writingToPointLimit = false;
      character_number = 0;
      return;
    case 2:
      writingToPointLimit = true;
      return;
    case 3:
      return;
  }
}
else if(checkIfEqual(A,GameType,4)){
  switch(clickedButton){
    case 0:
      copyArray(GameTypeTimeLimit,4);
      game_type = 1;
      return;
    case 1:
      in_menu = false;
      game_type = 0;
      return;
    case 2:
      return;
    case 3:
      copyArray(GameTypePointLimit,4);
      game_type = 2;
      return;
  }
}
else if(checkIfEqual(A,PauseScreen,4)){
  switch(clickedButton){
    case 0:
      in_menu = false;
      erase_sprite(mouse);
      return;
    case 1:
      return;
    case 2:
      copyArray(MainMenuSprites,7);
      point_limit = 0;
      max_time = 0;
      initialize_players();
      reset_ball();
      return;
    case 3:
      return;
    
  }
}
else if(checkIfEqual(A,WinScreen,8)){
  switch(clickedButton){
    case 0:
      return;
    case 1:
      writingName = true;
      return;
    case 2:
      
      return;
    case 3:
      
      return;
    case 4:
      
      return;
    case 5: case 6:
      copyArray(MainMenuSprites,7);
      point_limit = 0;
      max_time = 0;
      if(player2.score > player1.score && player2.score > highest_score){
        highest_score = player2.score;
        rtc_get_date();
        for(int i = 0; i < character_number; i++){
          highest_score_name[i] = name[i];
        }
        size_of_highscore_name = character_number;
        write_highscore_to_file();
        read_highscore_from_file();

      }else if(player1.score > player2.score && player1.score > highest_score){
        highest_score = player1.score;
        rtc_get_date(); 
        for(int i = 0; i < character_number; i++){
          highest_score_name[i] = name[i];
        }
        size_of_highscore_name = character_number;
        write_highscore_to_file();
        read_highscore_from_file();

        
      }
      character_number = 0;
      initialize_players();
      reset_ball();
      return;
    case 7:
      return;
  }
}
else if(checkIfEqual(A,HighScores,5)){
   switch (clickedButton)
   {
   case 4:
     copyArray(MainMenuSprites,7);
     return;
   
   default:
     return;
   }
  }


}

void control_player1(){
  
  if (scancode == S_KEY) {
        erase_sprite(player1.sprite[player1.current_sprite]);
        if (player1.y_speed < 0) player1.y_speed = -player1.y_speed;
        if (!(player1.sprite[player1.current_sprite].y == vmi_p.YResolution - ball_.sprite.height - player1.sprite[player1.current_sprite].height - 1 && ball_.sprite.y == vmi_p.YResolution - ball_.sprite.height)) {
          player1.sprite[player1.current_sprite].y = player1.sprite[player1.current_sprite].y + player1.y_speed;
        }
        if (player1.sprite[player1.current_sprite].y > vmi_p.YResolution - player1.sprite[player1.current_sprite].height) {
          player1.sprite[player1.current_sprite].y = vmi_p.YResolution - player1.sprite[player1.current_sprite].height;
        }
      }
      else if (scancode == W_KEY) {
        erase_sprite(player1.sprite[player1.current_sprite]);
        if (player1.y_speed > 0) player1.y_speed = -player1.y_speed;
        if (!(player1.sprite[player1.current_sprite].y == ball_.sprite.height + 1 && ball_.sprite.y == 0)) {
          player1.sprite[player1.current_sprite].y = player1.sprite[player1.current_sprite].y + player1.y_speed;
        }
        if (player1.sprite[player1.current_sprite].y < score.height + score.y +3) {
          player1.sprite[player1.current_sprite].y = score.height + score.y +3;
        }
      }
}

void control_player2(){
  if (counter == 0 && packet1.delta_y != 0) {
        
        if (packet1.delta_y > 2) {
          if (player2.y_speed > 0) player2.y_speed = -player2.y_speed;
          erase_sprite(player2.sprite[player2.current_sprite]);

          if (!(player2.sprite[player2.current_sprite].y == ball_.sprite.height - 1 && ball_.sprite.y == 0)) {
            player2.sprite[player2.current_sprite].y = player2.sprite[player2.current_sprite].y + player2.y_speed;
          }
        }
        else if (packet1.delta_y < -2) {
          if (player2.y_speed < 0) player2.y_speed = -player2.y_speed;
          erase_sprite(player2.sprite[player2.current_sprite]);
          if (!(player2.sprite[player2.current_sprite].y == vmi_p.YResolution - ball_.sprite.height - 1 && ball_.sprite.y == vmi_p.YResolution - ball_.sprite.height)) {
            player2.sprite[player2.current_sprite].y = player2.sprite[player2.current_sprite].y + player2.y_speed;
          }
        }
      
        if (player2.sprite[player2.current_sprite].y > vmi_p.YResolution - player2.sprite[player2.current_sprite].height) {
          player2.sprite[player2.current_sprite].y = vmi_p.YResolution - player2.sprite[player2.current_sprite].height;
        }
        else if (player2.sprite[player2.current_sprite].y < score.height + score.y + 3) {
          player2.sprite[player2.current_sprite].y = score.height + score.y + 3;
        }
        packet1.delta_y = 0;
  }
}


void realTimeWritting() {
  // writingtoTimeLimit  - max_time , point_limit
  // writingName bool - char[] , n sei em que x e y que se escreve o nome lol
  if ((writingToPointLimit || writingToTimeLimit) && character_number <= 25) {
    for (unsigned int i = 26; i < 36; i++) {
      if (scancode == big_numbers_and_letters[i].scancode) {
        character_number++;
        if (writingToPointLimit)
          point_limit = point_limit * 10 + (i - 26);
        if (writingToTimeLimit)
          max_time = max_time * 10 + (i - 26);
      }
      else if (scancode == 0x0E) {
        if (character_number > 0)
          character_number--;
        if (writingToPointLimit)
          point_limit = point_limit / 10;
        if (writingToTimeLimit)
          max_time = max_time / 10;
        scancode = 0x00;
      }
    }
  }
  else if (writingName) {
    for (unsigned int i = 0; i < 36; i++) {
      if (scancode == big_numbers_and_letters[i].scancode && character_number < 25) {

        if (i <= 25)
          name[character_number] = (char) (i + 65);
        else
          name[character_number] = (char) (i + 22);
        character_number++;
      }
      else if (scancode == 0x0E) {
        if (character_number > 0)
          character_number--;
        scancode = 0x00;
      }
    }
  }
  scancode = 0x00;
  double_buffer();
}

int ButtonClicked(struct Sprite buttons[], unsigned int size){
  for(unsigned int i = 0; i < size; i++){
    if(mouse.x > buttons[i].x && mouse.x <= buttons[i].x + buttons[i].width && mouse.y > buttons[i].y && mouse.y <= buttons[i].y + buttons[i].height){
      return i;
    }
  }
  return -1;
}

bool checkIfEqual(struct Sprite A[], struct Sprite B[], unsigned int size){
  for(unsigned int i = 0; i < size; i++ ){
    if(A[i].x != B[i].x || A[i].y != B[i].y || A[i].sprite1 != B[i].sprite1) return false;
  }
  return true;
}

void update_score(){
  //player 1 score
  int x = 50;
  vg_draw_rectangle(0,0, vmi_p.XResolution / 2 - score.width/2,score.height + score.y + 1,0);
  vg_draw_rectangle(vmi_p.XResolution / 2 + score.width / 2 + 10, 0, vmi_p.XResolution / 2 - score.width / 2, score.height + score.y + 1, 0);
  
  write_small_number_to_screen(player1.score,x,5,0xffffff);
  x = vmi_p.XResolution - 10;
  write_small_number_to_screen(player2.score,x,5,0xffffff);

  double_buffer(); 
}


void create_mouse(){
  mouse.x = vmi_p.XResolution / 2;
  mouse.y = vmi_p.YResolution / 2;
}

void reset_ball() {
  ball_.sprite.x = vmi_p.XResolution / 2;
  ball_.sprite.y = vmi_p.YResolution / 2;
  ball_.y_speed = 0;
  ball_.x_speed = 0;
  ball_.ball_speed = 7;
  while (ball_.y_speed == 0) {
    ball_.y_speed = ball_.ball_speed * ((rand() % 2) ? (-1) : 1);
  }
  while (ball_.x_speed == 0) {
    ball_.x_speed = ball_.ball_speed * ((rand() % 2) ? (-1) : 1);
  }
}

bool colision(struct Player *player) {
  for (int x = player->sprite[player->current_sprite].x; x <= player->sprite[player->current_sprite].x + player->sprite[player->current_sprite].width; x++) {
    for (int y = player->sprite[player->current_sprite].y; y <= player->sprite[player->current_sprite].y + player->sprite[player->current_sprite].height; y++) {
      if (is_colliding(x, y)) {
        int distanceFromTop = y - player->sprite[player->current_sprite].y;
        if(distanceFromTop < 2) distanceFromTop = 4;
        float bounceAngle = PI / 4 * (distanceFromTop / (float) player->sprite[player->current_sprite].height) - PI / 8;
        ball_.y_speed = sin(bounceAngle) * ball_.ball_speed;
        if (ball_.y_speed == 0) {
          ball_.y_speed = sin(bounceAngle - 10) * ball_.ball_speed;
        }
        ball_.x_speed = cos(bounceAngle) * ball_.ball_speed;
        if(player == &player2){
          ball_.x_speed = -ball_.x_speed;
        }
        return true;
      }
    }
  }
  return false;
}

bool overlap_save_p1() {
    //Drags ball with player if they move when the ball is still bellow/ above the player
  if (ball_.sprite.y <= player1.sprite[player1.current_sprite].y + player1.sprite[player1.current_sprite].height && ball_.sprite.y >= player1.sprite[player1.current_sprite].y) { // if the ball is currently clipped in the player
      if (ball_.sprite.x <= player1.sprite[player1.current_sprite].x + player1.sprite[player1.current_sprite].width) {
        if (player1.y_speed < 0) {  
                                                                                         //If the player moved up
          erase_sprite(ball_.sprite);                                                      //erase current ball
          if (player1.sprite[player1.current_sprite].y - ball_.sprite.height - 1 < score.height + score.y + 3) { // If dragging the ball up would result in it being out of bounds
            erase_sprite(player1.sprite[player1.current_sprite]);
            player1.sprite[player1.current_sprite].y = ball_.sprite.height + 1 + score.height + score.y + 3; // Player will be right under the ball
            ball_.sprite.y = score.height + score.y + 3;                                                     // Ball will be moved to the top of the screen
            return true;
          }
          else {
            ball_.sprite.y = player1.sprite[player1.current_sprite].y - ball_.sprite.height - 1; // moves the ball to the spot right above the player
            return true;
          }
        }
        else {                                                                                          // If the player moved down
          erase_sprite(ball_.sprite);                                                                   // Erases current ball
          if (player1.sprite[player1.current_sprite].y + player1.sprite[player1.current_sprite].height + ball_.sprite.height + 1 > vmi_p.YResolution) { // If dragging the ball down would result in it being out of bounds
            erase_sprite(player1.sprite[player1.current_sprite]);
            player1.sprite[player1.current_sprite].y = vmi_p.YResolution - ball_.sprite.height - player1.sprite[player1.current_sprite].height - 1; // Player will be moved to wight abose the ball
            ball_.sprite.y = vmi_p.YResolution - ball_.sprite.height;                               // Ball will be moved to the bottom most of the screen
            return true;
          }
          else {
            ball_.sprite.y = player1.sprite[player1.current_sprite].y + player1.sprite[player1.current_sprite].height + 1; // moves the ball to the spot right bellow the player
            return true;
          }
        }
      }
    }

    if (ball_.sprite.y + ball_.y_speed <= player1.sprite[player1.current_sprite].y + player1.sprite[player1.current_sprite].height && ball_.sprite.y + ball_.y_speed >= player1.sprite[player1.current_sprite].y) { //If the ball is going to overlap in its next movement
      if (ball_.sprite.x + ball_.x_speed <= player1.sprite[player1.current_sprite].x + player1.sprite[player1.current_sprite].width) {
        if (ball_.sprite.y <= player1.sprite[player1.current_sprite].y && ball_.sprite.x <= player1.sprite[player1.current_sprite].x + player1.sprite[player1.current_sprite].width) { // if the ball is overlaping with the player from above
          erase_sprite(ball_.sprite);
          ball_.sprite.y = player1.sprite[player1.current_sprite].y - ball_.sprite.height - 1; // changes the ball position to make sure it hits the player with out overlaping
          return true;
        }
        else if (ball_.sprite.y >= player1.sprite[player1.current_sprite].y + player1.sprite[player1.current_sprite].height && ball_.sprite.x <= player1.sprite[player1.current_sprite].x + player1.sprite[player1.current_sprite].width) { // if the ball is overlaping with the player from underneath
          erase_sprite(ball_.sprite);
          ball_.sprite.y = player1.sprite[player1.current_sprite].y + player1.sprite[player1.current_sprite].height + 1; // changes the ball position to make sure it hits the player with out overlaping
          return true;
        }
        else {
          erase_sprite(ball_.sprite);
          ball_.sprite.x = player1.sprite[player1.current_sprite].x + player1.sprite[player1.current_sprite].width + 1; // if it hits the side or corners it changes the x to avoid overlaping
          return true;
        }
      }
    }
    return false;
  }

bool overlap_save_p2(){

  //Drags ball with player if they move when the ball is still bellow/ above the player
  if (ball_.sprite.y <= player2.sprite[player2.current_sprite].y + player2.sprite[player2.current_sprite].height && ball_.sprite.y >= player2.sprite[player2.current_sprite].y) { // if the ball is currently clipped in the player
    if (ball_.sprite.x + ball_.sprite.width >= player2.sprite[player2.current_sprite].x) {
      if (player2.y_speed < 0){ //If the player moved up
        erase_sprite(ball_.sprite); //erase current ball
        if (player2.sprite[player2.current_sprite].y - ball_.sprite.height - 1 < score.height + score.y + 3) { // If dragging the ball up would result in it being out of bounds
          erase_sprite(player2.sprite[player2.current_sprite]);
          player2.sprite[player2.current_sprite].y = ball_.sprite.height + 1 + score.height + score.y + 3; // Player will be right under the ball
          ball_.sprite.y = score.height + score.y + 3;                                                     // Ball will be moved to the top of the screen
          return true;
        }
        else{
          ball_.sprite.y = player2.sprite[player2.current_sprite].y - ball_.sprite.height - 1; // moves the ball to the spot right above the player
          //debug_overlap("p2 up", player2);   
          return true;
        }
      }
      else{ // If the player moved down
        erase_sprite(ball_.sprite); // Erases current ball
        if (player2.sprite[player2.current_sprite].y + player2.sprite[player2.current_sprite].height + ball_.sprite.height + ball_.sprite.height + ball_.sprite.height / 2 + 1 > vmi_p.YResolution) { // If dragging the ball down would result in it being out of bounds
          erase_sprite(player2.sprite[player2.current_sprite]);
          player2.sprite[player2.current_sprite].y = vmi_p.YResolution - ball_.sprite.height - player2.sprite[player2.current_sprite].height - ball_.sprite.height / 2 - 1; // Player will be moved to wight abose the ball
          ball_.sprite.y = vmi_p.YResolution - ball_.sprite.height - ball_.sprite.height/2; // Ball will be moved to the bottom most of the screen
          return true;
        }
        else{
          ball_.sprite.y = player2.sprite[player2.current_sprite].y + player2.sprite[player2.current_sprite].height + 1; // moves the ball to the spot right bellow the player
          //debug_overlap("p2 down", player2);
          return true;
        }
      }
    }
  }

  if (ball_.sprite.y + ball_.y_speed <= player2.sprite[player2.current_sprite].y + player2.sprite[player2.current_sprite].height && ball_.sprite.y + ball_.y_speed >= player2.sprite[player2.current_sprite].y) { //If the ball is going to overlap in its next movement
    if (ball_.sprite.x + ball_.sprite.width + ball_.x_speed >= player2.sprite[player2.current_sprite].x) {
      if (ball_.sprite.y <= player2.sprite[player2.current_sprite].y && ball_.sprite.x + ball_.sprite.width >= player2.sprite[player2.current_sprite].x) { // if the ball is overlaping with the player from above
        erase_sprite(ball_.sprite);
        ball_.sprite.y = player2.sprite[player2.current_sprite].y - ball_.sprite.height - 1; // changes the ball position to make sure it hits the player with out overlaping
        //debug_overlap("p2 up", player2);
        return true;
      }
      else if (ball_.sprite.y >= player2.sprite[player2.current_sprite].y + player2.sprite[player2.current_sprite].height && ball_.sprite.x + ball_.sprite.width >= player2.sprite[player2.current_sprite].x) { // if the ball is overlaping with the player from underneath
        erase_sprite(ball_.sprite);
        ball_.sprite.y = player2.sprite[player2.current_sprite].y + player2.sprite[player2.current_sprite].height + 1; // changes the ball position to make sure it hits the player with out overlaping
        //debug_overlap("p2 down", player2);
        return true;
      }
      else{
        erase_sprite(ball_.sprite);
        ball_.sprite.x = player2.sprite[player2.current_sprite].x - ball_.sprite.width - 1; // if it hits the side or corners it changes the x to avoid overlaping
        return true;
      }
    }
  }
  return false;
}

bool is_colliding(int x, int y) {
  int center_x = ball_.sprite.x + ball_.sprite.width / 2;
  int center_y = ball_.sprite.y + ball_.sprite.height / 2;
  int radius = ball_.sprite.height / 2 + 1;
  int a = ((x - center_x) * (x - center_x)  + (y - center_y) * (y - center_y));
  int b = radius * radius;
  return (a == b);
}
