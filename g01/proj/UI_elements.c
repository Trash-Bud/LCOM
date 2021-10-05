#include "UI_elements.h"
#include "include_xpms.h"
#include "logic.h"
#include "power_up.h"


/// <summary>
/// Main menu sprites
/// </summary>
struct Sprite MainMenuSprites[7];
/// <summary>
/// Resolutions menu sprites
/// </summary>
struct Sprite ResolutionsMenu[6];
/// <summary>
/// Game type time limit menu sprites
/// </summary>
struct Sprite GameTypeTimeLimit[4];
/// <summary>
/// Game type point limit menu sprites
/// </summary>
struct Sprite GameTypePointLimit[4];
/// <summary>
/// Choosing game type menu sprites
/// </summary>
struct Sprite GameType[4];
extern struct PowerUp Power_ups[3];
/// <summary>
/// Pause menu sprites
/// </summary>
struct Sprite PauseScreen[4];
/// <summary>
/// Win menu sprites
/// </summary>
struct Sprite WinScreen[8];
/// <summary>
/// Highscore menu sprites
/// </summary>
struct Sprite HighScores[5];
/// <summary>
/// array with all the sprites for hovering buttons
/// </summary>
struct Sprite HoverButtons[16];
/// <summary>
/// size of the current menu
/// </summary>
int size_menu = 0;
/// <summary>
/// array with all sprites for big numbers and for letters
/// </summary>
struct Sprite big_numbers_and_letters[36];
/// <summary>
/// array with all sprites for small numbers including a '-' and a ':'
/// </summary>
struct Sprite small_numbers[12];
/// <summary>
/// type for using xpm_load()
/// </summary>
enum xpm_image_type type;
extern struct Player player1, player2;
extern vbe_mode_info_t vmi_p;
extern struct Sprite score;
extern struct Sprite mouse;
extern struct Ball ball_;


void load_mode_0x11A(){
 xpm_image_t img;
  struct Animation fire_powerUp;
  struct Animation increase_powerUp;
  struct Animation decrease_powerUp;
  struct Sprite a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, travessao, dois_pontos;
  struct Sprite small0, small1, small2, small3, small4, small5, small6, small7, small8, small9;
  struct Sprite big0, big1, big2, big3, big4, big5, big6, big7, big8, big9;
  struct Sprite res1, res2, res4, res5, done, endless, exit1, game_type, help, highscore_field, highscores, highscore_title,
    local, name_input, name, new_highscore, options, pause1, player1_won, player2_won, point_limit_input, points, quit, remote,
    resolution, resume, time_limit_minutes, time1, title, point_limit, draw1;


      //HOVER//
  local.sprite1 = xpm_load(button_1152x864_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[0] = local;

  local.sprite1 = xpm_load(button_1280x1024_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[1] = local;

  local.sprite1 = xpm_load(button_640x480_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[2] = local;

  local.sprite1 = xpm_load(button_800x600_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[3] = local;

  local.sprite1 = xpm_load(button_done_hover___0x11A,type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[4] = local;

  local.sprite1 = xpm_load(button_endless_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[5] = local;

  local.sprite1 = xpm_load(button_exit_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[6] = local;

  local.sprite1 = xpm_load(button_help_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[7] = local;

  local.sprite1 = xpm_load(button_highscores_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[8] = local;

  local.sprite1 = xpm_load(button_local_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[9] = local;

  local.sprite1 = xpm_load(button_option_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[10] = local;

  local.sprite1 = xpm_load(button_points_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[11] = local;

  local.sprite1 = xpm_load(button_quit_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[12] = local;

  local.sprite1 = xpm_load(button_remote_hover___, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[13] = local;

  local.sprite1 = xpm_load(button_time_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[14] = local;

  local.sprite1 = xpm_load(button_resume_hover___0x11A, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[15] = local;



  fire_powerUp.number_of_frames = 6;
  fire_powerUp.frames[0].sprite1 = xpm_load(FIREFRAME0_, type, &img);
  fire_powerUp.frames[0].width = img.width;
  fire_powerUp.frames[0].height = img.height;

  fire_powerUp.frames[1].sprite1 = xpm_load(FIREFRAME1_, type, &img);
  fire_powerUp.frames[1].width = img.width;
  fire_powerUp.frames[1].height = img.height;

  fire_powerUp.frames[2].sprite1 = xpm_load(FIREFRAME2_, type, &img);
  fire_powerUp.frames[2].width = img.width;
  fire_powerUp.frames[2].height = img.height;

  fire_powerUp.frames[3].sprite1 = xpm_load(FIREFRAME3_, type, &img);
  fire_powerUp.frames[3].width = img.width;
  fire_powerUp.frames[3].height = img.height;

  fire_powerUp.frames[4].sprite1 = xpm_load(FIREFRAME4_, type, &img);
  fire_powerUp.frames[4].width = img.width;
  fire_powerUp.frames[4].height = img.height;

  fire_powerUp.frames[5].sprite1 = xpm_load(FIREFRAME5_, type, &img);
  fire_powerUp.frames[5].width = img.width;
  fire_powerUp.frames[5].height = img.height;

  Power_ups[0].animation = fire_powerUp;


  //INCREASE POWERUP

  increase_powerUp.number_of_frames = 3;
  increase_powerUp.frames[0].sprite1 = xpm_load(INCREASE0_, type, &img);
  increase_powerUp.frames[0].width = img.width;
  increase_powerUp.frames[0].height = img.height;

  increase_powerUp.frames[1].sprite1 = xpm_load(INCREASE1_, type, &img);
  increase_powerUp.frames[1].width = img.width;
  increase_powerUp.frames[1].height = img.height;

  increase_powerUp.frames[2].sprite1 = xpm_load(INCREASE2_, type, &img);
  increase_powerUp.frames[2].width = img.width;
  increase_powerUp.frames[2].height = img.height;

  Power_ups[1].animation = increase_powerUp;
  

  //DECREASE POWERUP
  decrease_powerUp.number_of_frames = 3;

  decrease_powerUp.frames[0].sprite1 = xpm_load(DECREASE0_, type, &img);
  decrease_powerUp.frames[0].width = img.width;
  decrease_powerUp.frames[0].height = img.height;

  decrease_powerUp.frames[1].sprite1 = xpm_load(DECREASE1_, type, &img);
  decrease_powerUp.frames[1].width = img.width;
  decrease_powerUp.frames[1].height = img.height;

  decrease_powerUp.frames[2].sprite1 = xpm_load(DECREASE2_, type, &img);
  decrease_powerUp.frames[2].width = img.width;
  decrease_powerUp.frames[2].height = img.height;

  Power_ups[2].animation = decrease_powerUp;
  

  //CURSOR
  mouse.sprite1 = xpm_load(cursor, type, &img);
  mouse.width = img.width;
  mouse.height = img.height;
 

  //PLAYERS
  player1.current_sprite = 0;

  player1.sprite[0].sprite1 = xpm_load(PLAYERMED, type, &img);
  player1.sprite[0].width = img.width;
  player1.sprite[0].height = img.height;

  player1.sprite[1].sprite1 = xpm_load(PLAYERSMALL, type, &img);
  player1.sprite[1].width = img.width;
  player1.sprite[1].height = img.height;

  player1.sprite[2].sprite1 = xpm_load(PLAYERBIG, type, &img);
  player1.sprite[2].width = img.width;
  player1.sprite[2].height = img.height;

  player2 = player1;
  

  ball_.sprite.sprite1 = xpm_load(BALL__, type, &img);
  ball_.sprite.width = img.width;
  ball_.sprite.height = img.height;

  score.sprite1 = xpm_load(_SCORE_, type, &img);
  score.width = img.width;
  score.height = img.height;
  score.x = vmi_p.XResolution / 2 - score.width / 2;
  score.y = 5;
  struct Sprite score1 = score;
  score1.x = 113;
  score1.y = 259;
  HighScores[3] = score1;

  draw1.sprite1 = xpm_load(draw_0x11a, type, &img);
  draw1.width = img.width;
  draw1.height = img.height;
  draw1.x = 2;
  draw1.y = 281;
  WinScreen[7] = draw1;

  a.sprite1 = xpm_load(A_, type, &img);
  a.width = img.width;
  a.height = img.height;
  a.scancode = 0x1E;
  big_numbers_and_letters[0] = a;

  b.sprite1 = xpm_load(B_, type, &img);
  b.width = img.width;
  b.height = img.height;
  b.scancode = 0x30;
  big_numbers_and_letters[1] = b;

  c.sprite1 = xpm_load(C_, type, &img);
  c.width = img.width;
  c.height = img.height;
  c.scancode = 0x2E;
  big_numbers_and_letters[2] = c;

  d.sprite1 = xpm_load(D_, type, &img);
  d.width = img.width;
  d.height = img.height;
  d.scancode = 0x20;
  big_numbers_and_letters[3] = d;

  e.sprite1 = xpm_load(E_, type, &img);
  e.width = img.width;
  e.height = img.height;
  e.scancode = 0x12;
  big_numbers_and_letters[4] = e;

  f.sprite1 = xpm_load(F_, type, &img);
  f.width = img.width;
  f.height = img.height;
  f.scancode = 0x21;
  big_numbers_and_letters[5] = f;

  g.sprite1 = xpm_load(G_, type, &img);
  g.width = img.width;
  g.height = img.height;
  g.scancode = 0x22;
  big_numbers_and_letters[6] = g;

  h.sprite1 = xpm_load(H_, type, &img);
  h.width = img.width;
  h.height = img.height;
  h.scancode = 0x23;
  big_numbers_and_letters[7] = h;

  i.sprite1 = xpm_load(I_, type, &img);
  i.width = img.width;
  i.height = img.height;
  i.scancode = 0x17;
  big_numbers_and_letters[8] = i;

  j.sprite1 = xpm_load(J_, type, &img);
  j.width = img.width;
  j.height = img.height;
  j.scancode = 0x24;
  big_numbers_and_letters[9] = j;

  k.sprite1 = xpm_load(K_, type, &img);
  k.width = img.width;
  k.height = img.height;
  k.scancode = 0x25;
  big_numbers_and_letters[10] = k;

  l.sprite1 = xpm_load(L_, type, &img);
  l.width = img.width;
  l.height = img.height;
  l.scancode = 0x26;
  big_numbers_and_letters[11] = l;

  m.sprite1 = xpm_load(M_, type, &img);
  m.width = img.width;
  m.height = img.height;
  m.scancode = 0x32;
  big_numbers_and_letters[12] = m;

  n.sprite1 = xpm_load(N_, type, &img);
  n.width = img.width;
  n.height = img.height;
  n.scancode = 0x31;
  big_numbers_and_letters[13] = n;

  o.sprite1 = xpm_load(O_, type, &img);
  o.width = img.width;
  o.height = img.height;
  o.scancode = 0x18;
  big_numbers_and_letters[14] = o;

  p.sprite1 = xpm_load(P_, type, &img);
  p.width = img.width;
  p.height = img.height;
  p.scancode = 0x19;
  big_numbers_and_letters[15] = p;

  q.sprite1 = xpm_load(Q_, type, &img);
  q.width = img.width;
  q.height = img.height;
  q.scancode = 0x10;
  big_numbers_and_letters[16] = q;

  r.sprite1 = xpm_load(R_, type, &img);
  r.width = img.width;
  r.height = img.height;
  r.scancode = 0x13;
  big_numbers_and_letters[17] = r;

  s.sprite1 = xpm_load(S_, type, &img);
  s.width = img.width;
  s.height = img.height;
  s.scancode = 0x1f;
  big_numbers_and_letters[18] = s;

  t.sprite1 = xpm_load(T_, type, &img);
  t.width = img.width;
  t.height = img.height;
  t.scancode = 0x14;
  big_numbers_and_letters[19] = t;

  u.sprite1 = xpm_load(U_, type, &img);
  u.width = img.width;
  u.height = img.height;
  u.scancode = 0x16;
  big_numbers_and_letters[20] = u;

  v.sprite1 = xpm_load(V_, type, &img);
  v.width = img.width;
  v.height = img.height;
  v.scancode = 0x2F;
  big_numbers_and_letters[21] = v;

  w.sprite1 = xpm_load(W_, type, &img);
  w.width = img.width;
  w.height = img.height;
  w.scancode = 0x11;
  big_numbers_and_letters[22] = w;

  x.sprite1 = xpm_load(X_, type, &img);
  x.width = img.width;
  x.height = img.height;
  x.scancode = 0x2D;
  big_numbers_and_letters[23] = x;

  y.sprite1 = xpm_load(Y_, type, &img);
  y.width = img.width;
  y.height = img.height;
  y.scancode = 0x15;
  big_numbers_and_letters[24] = y;

  z.sprite1 = xpm_load(Z_, type, &img);
  z.width = img.width;
  z.height = img.height;
  z.scancode = 0x2C;
  big_numbers_and_letters[25] = z;

  travessao.sprite1 = xpm_load(SMALLTRAVESSAO_, type, &img);
  travessao.width = img.width;
  travessao.height = img.height;
  travessao.scancode = 0x35;
  small_numbers[0] = travessao;

  dois_pontos.sprite1 = xpm_load(SMALLDOISPONTOS_, type, &img);
  dois_pontos.width = img.width;
  dois_pontos.height = img.height;
  dois_pontos.scancode = 0x34;
  small_numbers[1] = dois_pontos;

  small0.sprite1 = xpm_load(SMALL0_, type, &img);
  small0.width = img.width;
  small0.height = img.height;
  small0.scancode = 0x0B;
  small_numbers[2] = small0;

  small1.sprite1 = xpm_load(SMALL1_, type, &img);
  small1.width = img.width;
  small1.height = img.height;
  small1.scancode = 0x02;
  small_numbers[3] = small1;

  small2.sprite1 = xpm_load(SMALL2_, type, &img);
  small2.width = img.width;
  small2.height = img.height;
  small2.scancode = 0x03;
  small_numbers[4] = small2;

  small3.sprite1 = xpm_load(SMALL3_, type, &img);
  small3.width = img.width;
  small3.height = img.height;
  small3.scancode = 0x04;
  small_numbers[5] = small3;

  small4.sprite1 = xpm_load(SMALL4_, type, &img);
  small4.width = img.width;
  small4.height = img.height;
  small4.scancode = 0x05;
  small_numbers[6] = small4;

  small5.sprite1 = xpm_load(SMALL5_, type, &img);
  small5.width = img.width;
  small5.height = img.height;
  small5.scancode = 0x06;
  small_numbers[7] = small5;

  small6.sprite1 = xpm_load(SMALL6_, type, &img);
  small6.width = img.width;
  small6.height = img.height;
  small6.scancode = 0x07;
  small_numbers[8] = small6;

  small7.sprite1 = xpm_load(SMALL7_, type, &img);
  small7.width = img.width;
  small7.height = img.height;
  small7.scancode = 0x08;
  small_numbers[9] = small7;

  small8.sprite1 = xpm_load(SMALL8_, type, &img);
  small8.width = img.width;
  small8.height = img.height;
  small8.scancode = 0x09;
  small_numbers[10] = small8;

  small9.sprite1 = xpm_load(SMALL9_, type, &img);
  small9.width = img.width;
  small9.height = img.height;
  small9.scancode = 0x0A;
  small_numbers[11] = small9;

  big0.sprite1 = xpm_load(BIG0_, type, &img);
  big0.width = img.width;
  big0.height = img.height;
  big0.scancode = 0x0B;
  big_numbers_and_letters[26] = big0;

  big1.sprite1 = xpm_load(BIG1_, type, &img);
  big1.width = img.width;
  big1.height = img.height;
  big1.scancode = 0x02;
  big_numbers_and_letters[27] = big1;

  big2.sprite1 = xpm_load(BIG2_, type, &img);
  big2.width = img.width;
  big2.height = img.height;
  big2.scancode = 0x03;
  big_numbers_and_letters[28] = big2;

  big3.sprite1 = xpm_load(BIG3_, type, &img);
  big3.width = img.width;
  big3.height = img.height;
  big3.scancode = 0x04;
  big_numbers_and_letters[29] = big3;

  big4.sprite1 = xpm_load(BIG4_, type, &img);
  big4.width = img.width;
  big4.height = img.height;
  big4.scancode = 0x05;
  big_numbers_and_letters[30] = big4;

  big5.sprite1 = xpm_load(BIG5_, type, &img);
  big5.width = img.width;
  big5.height = img.height;
  big5.scancode = 0x06;
  big_numbers_and_letters[31] = big5;

  big6.sprite1 = xpm_load(BIG6_, type, &img);
  big6.width = img.width;
  big6.height = img.height;
  big6.scancode = 0x07;
  big_numbers_and_letters[32] = big6;

  big7.sprite1 = xpm_load(BIG7_, type, &img);
  big7.width = img.width;
  big7.height = img.height;
  big7.scancode = 0x08;
  big_numbers_and_letters[33] = big7;

  big8.sprite1 = xpm_load(BIG8_, type, &img);
  big8.width = img.width;
  big8.height = img.height;
  big8.scancode = 0x09;
  big_numbers_and_letters[34] = big8;

  big9.sprite1 = xpm_load(BIG9_, type, &img);
  big9.width = img.width;
  big9.height = img.height;
  big9.scancode = 0x0A;
  big_numbers_and_letters[35] = big9;

  point_limit.sprite1 = xpm_load(TYPETHEPOINTLIMIT_, type, &img);
  point_limit.width = img.width;
  point_limit.height = img.height;
  point_limit.x = 436;
  point_limit.y = 398;
  GameTypePointLimit[0] = point_limit;

  title.sprite1 = xpm_load(TITLE__, type, &img);
  title.width = img.width;
  title.height = img.height;
  title.x = 316;
  title.y = 137;
  MainMenuSprites[0] = title;
  PauseScreen[3] = title;
  WinScreen[0] = title;

  time1.sprite1 = xpm_load(TIME__, type, &img);
  time1.width = img.width;
  time1.height = img.height;
  time1.x = 113;
  time1.y = 471;

  GameType[0] = time1;

  time_limit_minutes.sprite1 = xpm_load(TIMELIMITEINSECONDS_, type, &img);
  time_limit_minutes.width = img.width;
  time_limit_minutes.height = img.height;
  time_limit_minutes.x = 298;
  time_limit_minutes.y = 398;

  GameTypeTimeLimit[0] = time_limit_minutes;

  resume.sprite1 = xpm_load(RESUME__, type, &img);
  resume.width = img.width;
  resume.height = img.height;
  resume.x = 173;
  resume.y = 530;

  PauseScreen[0] = resume;

  res1.sprite1 = xpm_load(res640x480_, type, &img);
  res1.width = img.width;
  res1.height = img.height;
  res1.x = 357;
  res1.y = 328;

  ResolutionsMenu[0] = res1;

  res2.sprite1 = xpm_load(res800x600_, type, &img);
  res2.width = img.width;
  res2.height = img.height;
  res2.x = 357;
  res2.y = 436;

  ResolutionsMenu[1] = res2;


  res4.sprite1 = xpm_load(res1152x864_, type, &img);
  res4.width = img.width;
  res4.height = img.height;
  res4.x = 357;
  res4.y = 641;

  ResolutionsMenu[2] = res4;
  res5.sprite1 = xpm_load(res1280x1024_, type, &img);
  res5.width = img.width;
  res5.height = img.height;
  res5.x = 357;
  res5.y = 539;

  ResolutionsMenu[3] = res5;

  done.sprite1 = xpm_load(DONE__, type, &img);
  done.width = img.width;
  done.height = img.height;
  done.x = 460;
  done.y = 834;
  GameTypePointLimit[1] = done;
  GameTypeTimeLimit[1] = done;
  ResolutionsMenu[4] = done;
  HighScores[4] = done;

  endless.sprite1 = xpm_load(ENDLESS__, type, &img);
  endless.width = img.width;
  endless.height = img.height;
  endless.x = 427;
  endless.y = 286;
  GameType[1] = endless;

  resolution.sprite1 = xpm_load(RESOLUTION__, type, &img);
  resolution.width = img.width;
  resolution.height = img.height;
  resolution.x = 371;
  resolution.y = 73;

  ResolutionsMenu[5] = resolution;

  exit1.sprite1 = xpm_load(EXIT__, type, &img);
  exit1.width = img.width;
  exit1.height = img.height;
  exit1.x = 501;
  exit1.y = 896;
  MainMenuSprites[1] = exit1;

  game_type.sprite1 = xpm_load(GAMETYPE, type, &img);
  game_type.width = img.width;
  game_type.height = img.height;
  game_type.x = 389;
  game_type.y = 59;
  GameType[2] = game_type;
  GameTypePointLimit[3] = game_type;
  GameTypeTimeLimit[3] = game_type;

  help.sprite1 = xpm_load(HELP__, type, &img);
  help.width = img.width;
  help.height = img.height;
  help.x = 501;
  help.y = 806;
  MainMenuSprites[2] = help;

  highscore_field.sprite1 = xpm_load(HIGHSCOREFIELDS_, type, &img);
  highscore_field.width = img.width;
  highscore_field.height = img.height;
  highscore_field.x = 110;
  highscore_field.y = 310;
  HighScores[2] = highscore_field;

  highscores.sprite1 = xpm_load(HIGHSCORES__, type, &img);
  highscores.width = img.width;
  highscores.height = img.height;
  highscores.x = 329;
  highscores.y = 629;
  MainMenuSprites[3] = highscores;

  highscore_title.sprite1 = xpm_load(HIGHSCORETITLE, type, &img);
  highscore_title.width = img.width;
  highscore_title.height = img.height;
  highscore_title.x = 363;
  highscore_title.y = 59;
  HighScores[0] = highscore_title;

  local.sprite1 = xpm_load(LOCAL__, type, &img);
  local.width = img.width;
  local.height = img.height;
  local.x = 31;
  local.y = 380;
  MainMenuSprites[4] = local;

  name_input.sprite1 = xpm_load(BALLFORNAMEINPUTWHENAHIGHSCOREHAPPENS, type, &img);
  name_input.width = img.width;
  name_input.height = img.height;
  name_input.x = 207;
  name_input.y = 667;
  WinScreen[1] = name_input;

  name.sprite1 = xpm_load(NAME___, type, &img);
  name.width = img.width;
  name.height = img.height;
  name.x = 500;
  name.y = 259;
  HighScores[1] = name;

  new_highscore.sprite1 = xpm_load(NEWHIGHSCORES, type, &img);
  new_highscore.width = img.width;
  new_highscore.height = img.height;
  new_highscore.x = 195;
  new_highscore.y = 563;
  WinScreen[2] = new_highscore;

  options.sprite1 = xpm_load(OPTIONS__, type, &img);
  options.width = img.width;
  options.height = img.height;
  options.x = 429;
  options.y = 717;
  MainMenuSprites[5] = options;

  pause1.sprite1 = xpm_load(PAUSE__, type, &img);
  pause1.width = img.width;
  pause1.height = img.height;
  pause1.x = 458;
  pause1.y = 290;
  PauseScreen[1] = pause1;

  player1_won.sprite1 = xpm_load(PLAYER1WON_, type, &img);
  player1_won.width = img.width;
  player1_won.height = img.height;
  player1_won.x = 250;
  player1_won.y = 281;
  WinScreen[3] = player1_won;

  player2_won.sprite1 = xpm_load(PLAYER2WON_, type, &img);
  player2_won.width = img.width;
  player2_won.height = img.height;
  player2_won.x = 250;
  player2_won.y = 281;
  WinScreen[4] = player2_won;

  point_limit_input.sprite1 = xpm_load(BARFORTIMEPOINTSINPUT_, type, &img);
  point_limit_input.width = img.width;
  point_limit_input.height = img.height;
  point_limit_input.x = 248;
  point_limit_input.y = 442;
  GameTypePointLimit[2] = point_limit_input;
  GameTypeTimeLimit[2] = point_limit_input;

  points.sprite1 = xpm_load(POINTS__, type, &img);
  points.width = img.width;
  points.height = img.height;
  points.x = 728;
  points.y = 469;
  GameType[3] = points;

  quit.sprite1 = xpm_load(QUIT__, type, &img);
  quit.width = img.width;
  quit.height = img.height;
  quit.x = 423;
  quit.y = 819;
  struct Sprite quit_highscore = quit;
  quit_highscore.x = 423;
  quit_highscore.y = 819;
  struct Sprite quit_pause = quit;
  quit_pause.x = 673;
  quit_pause.y = 530;
  PauseScreen[2] = quit_pause;
  WinScreen[5] = quit;
  WinScreen[6] = quit_highscore;

  remote.sprite1 = xpm_load(REMOTE__, type, &img);
  remote.width = img.width;
  remote.height = img.height;
  remote.x = 765;
  remote.y = 380;
  MainMenuSprites[6] = remote;


}



void load_mode_0x14C() {
  xpm_image_t img;
  struct Animation fire_powerUp;
  struct Animation increase_powerUp;
  struct Animation decrease_powerUp;
  struct Sprite a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, travessao, dois_pontos;
  struct Sprite small0, small1, small2, small3, small4, small5, small6, small7, small8, small9;
  struct Sprite big0, big1, big2, big3, big4, big5, big6, big7, big8, big9;
  struct Sprite res1, res2, res4, res5, done, endless, exit1, game_type, help, highscore_field, highscores, highscore_title,
    local, name_input, name, new_highscore, options, pause1, player1_won, player2_won, point_limit_input, points, quit, remote,
    resolution, resume, time_limit_minutes, time1, title, point_limit, draw1;


    //HOVER//
  local.sprite1 = xpm_load(button_1152x864_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[0] = local;

  local.sprite1 = xpm_load(button_1280x1024_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[1] = local;

  local.sprite1 = xpm_load(button_640x480_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[2] = local;

  local.sprite1 = xpm_load(button_800x600_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[3] = local;

  local.sprite1 = xpm_load(button_done_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[4] = local;

  local.sprite1 = xpm_load(button_endless_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[5] = local;

  local.sprite1 = xpm_load(button_exit_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[6] = local;

  local.sprite1 = xpm_load(button_help_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[7] = local;

  local.sprite1 = xpm_load(button_highscores_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[8] = local;

  local.sprite1 = xpm_load(button_local_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[9] = local;

  local.sprite1 = xpm_load(button_options_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[10] = local;

  local.sprite1 = xpm_load(button_points_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[11] = local;

  local.sprite1 = xpm_load(button_quit_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[12] = local;

  local.sprite1 = xpm_load(button_remote_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[13] = local;

  local.sprite1 = xpm_load(button_time_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[14] = local;

  local.sprite1 = xpm_load(button_resume_hover_0x14C, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[15] = local;


  //FIRE POWERUP

  fire_powerUp.number_of_frames = 6;
  fire_powerUp.frames[0].sprite1 = xpm_load(fire_0, type, &img);
  fire_powerUp.frames[0].width = img.width;
  fire_powerUp.frames[0].height = img.height;

  fire_powerUp.frames[1].sprite1 = xpm_load(fire_1, type, &img);
  fire_powerUp.frames[1].width = img.width;
  fire_powerUp.frames[1].height = img.height;

  fire_powerUp.frames[2].sprite1 = xpm_load(fire_2, type, &img);
  fire_powerUp.frames[2].width = img.width;
  fire_powerUp.frames[2].height = img.height;

  fire_powerUp.frames[3].sprite1 = xpm_load(fire_3, type, &img);
  fire_powerUp.frames[3].width = img.width;
  fire_powerUp.frames[3].height = img.height;

  fire_powerUp.frames[4].sprite1 = xpm_load(fire_4, type, &img);
  fire_powerUp.frames[4].width = img.width;
  fire_powerUp.frames[4].height = img.height;

  fire_powerUp.frames[5].sprite1 = xpm_load(fire_5, type, &img);
  fire_powerUp.frames[5].width = img.width;
  fire_powerUp.frames[5].height = img.height;

  Power_ups[0].animation = fire_powerUp;


  //INCREASE POWERUP

  increase_powerUp.number_of_frames = 3;
  increase_powerUp.frames[0].sprite1 = xpm_load(increase_0, type, &img);
  increase_powerUp.frames[0].width = img.width;
  increase_powerUp.frames[0].height = img.height;

  increase_powerUp.frames[1].sprite1 = xpm_load(increase_1, type, &img);
  increase_powerUp.frames[1].width = img.width;
  increase_powerUp.frames[1].height = img.height;

  increase_powerUp.frames[2].sprite1 = xpm_load(increase_2, type, &img);
  increase_powerUp.frames[2].width = img.width;
  increase_powerUp.frames[2].height = img.height;

  Power_ups[1].animation = increase_powerUp;

  //DECREASE POWERUP
  decrease_powerUp.number_of_frames = 3;

  decrease_powerUp.frames[0].sprite1 = xpm_load(decrease_0, type, &img);
  decrease_powerUp.frames[0].width = img.width;
  decrease_powerUp.frames[0].height = img.height;

  decrease_powerUp.frames[1].sprite1 = xpm_load(decrease_1, type, &img);
  decrease_powerUp.frames[1].width = img.width;
  decrease_powerUp.frames[1].height = img.height;

  decrease_powerUp.frames[2].sprite1 = xpm_load(decrease_2, type, &img);
  decrease_powerUp.frames[2].width = img.width;
  decrease_powerUp.frames[2].height = img.height;

  Power_ups[2].animation = decrease_powerUp;

  //CURSOR
  mouse.sprite1 = xpm_load(cursor, type, &img);
  mouse.width = img.width;
  mouse.height = img.height;
  

  //PLAYERS
  player1.current_sprite = 0;

  player1.sprite[0].sprite1 = xpm_load(med_player, type, &img);
  player1.sprite[0].width = img.width;
  player1.sprite[0].height = img.height;

  player1.sprite[1].sprite1 = xpm_load(small_player, type, &img);
  player1.sprite[1].width = img.width;
  player1.sprite[1].height = img.height;

  player1.sprite[2].sprite1 = xpm_load(big_player, type, &img);
  player1.sprite[2].width = img.width;
  player1.sprite[2].height = img.height;

  player2 = player1;


  ball_.sprite.sprite1 = xpm_load(ball_2, type, &img);
  ball_.sprite.width = img.width;
  ball_.sprite.height = img.height;

  score.sprite1 = xpm_load(score___, type, &img);
  score.width = img.width;
  score.height = img.height;
  score.x = vmi_p.XResolution / 2 - score.width / 2;
  score.y = 5;
  struct Sprite score1 = score;
  score1.x = 101;
  score1.y = 229;
  HighScores[3] = score1;

  draw1.sprite1 = xpm_load(draw__, type, &img);
  draw1.width = img.width;
  draw1.height = img.height;
  draw1.x = 1;
  draw1.y = 223;
  WinScreen[7] = draw1;

  a.sprite1 = xpm_load(a__, type, &img);
  a.width = img.width;
  a.height = img.height;
  a.scancode = 0x1E;
  big_numbers_and_letters[0] = a;

  b.sprite1 = xpm_load(b__, type, &img);
  b.width = img.width;
  b.height = img.height;
  b.scancode = 0x30;
  big_numbers_and_letters[1] = b;

  c.sprite1 = xpm_load(c__, type, &img);
  c.width = img.width;
  c.height = img.height;
  c.scancode = 0x2E;
  big_numbers_and_letters[2] = c;

  d.sprite1 = xpm_load(d__, type, &img);
  d.width = img.width;
  d.height = img.height;
  d.scancode = 0x20;
  big_numbers_and_letters[3] = d;

  e.sprite1 = xpm_load(e__, type, &img);
  e.width = img.width;
  e.height = img.height;
  e.scancode = 0x12;
  big_numbers_and_letters[4] = e;

  f.sprite1 = xpm_load(f__, type, &img);
  f.width = img.width;
  f.height = img.height;
  f.scancode = 0x21;
  big_numbers_and_letters[5] = f;

  g.sprite1 = xpm_load(g__, type, &img);
  g.width = img.width;
  g.height = img.height;
  g.scancode = 0x22;
  big_numbers_and_letters[6] = g;

  h.sprite1 = xpm_load(h__, type, &img);
  h.width = img.width;
  h.height = img.height;
  h.scancode = 0x23;
  big_numbers_and_letters[7] = h;

  i.sprite1 = xpm_load(i__, type, &img);
  i.width = img.width;
  i.height = img.height;
  i.scancode = 0x17;
  big_numbers_and_letters[8] = i;

  j.sprite1 = xpm_load(j__, type, &img);
  j.width = img.width;
  j.height = img.height;
  j.scancode = 0x24;
  big_numbers_and_letters[9] = j;

  k.sprite1 = xpm_load(k__, type, &img);
  k.width = img.width;
  k.height = img.height;
  k.scancode = 0x25;
  big_numbers_and_letters[10] = k;

  l.sprite1 = xpm_load(l__, type, &img);
  l.width = img.width;
  l.height = img.height;
  l.scancode = 0x26;
  big_numbers_and_letters[11] = l;

  m.sprite1 = xpm_load(m__, type, &img);
  m.width = img.width;
  m.height = img.height;
  m.scancode = 0x32;
  big_numbers_and_letters[12] = m;

  n.sprite1 = xpm_load(n__, type, &img);
  n.width = img.width;
  n.height = img.height;
  n.scancode = 0x31;
  big_numbers_and_letters[13] = n;

  o.sprite1 = xpm_load(o__, type, &img);
  o.width = img.width;
  o.height = img.height;
  o.scancode = 0x18;
  big_numbers_and_letters[14] = o;

  p.sprite1 = xpm_load(p__, type, &img);
  p.width = img.width;
  p.height = img.height;
  p.scancode = 0x19;
  big_numbers_and_letters[15] = p;

  q.sprite1 = xpm_load(q__, type, &img);
  q.width = img.width;
  q.height = img.height;
  q.scancode = 0x10;
  big_numbers_and_letters[16] = q;

  r.sprite1 = xpm_load(r__, type, &img);
  r.width = img.width;
  r.height = img.height;
  r.scancode = 0x13;
  big_numbers_and_letters[17] = r;

  s.sprite1 = xpm_load(s__, type, &img);
  s.width = img.width;
  s.height = img.height;
  s.scancode = 0x1f;
  big_numbers_and_letters[18] = s;

  t.sprite1 = xpm_load(t__, type, &img);
  t.width = img.width;
  t.height = img.height;
  t.scancode = 0x14;
  big_numbers_and_letters[19] = t;

  u.sprite1 = xpm_load(u__, type, &img);
  u.width = img.width;
  u.height = img.height;
  u.scancode = 0x16;
  big_numbers_and_letters[20] = u;

  v.sprite1 = xpm_load(v__, type, &img);
  v.width = img.width;
  v.height = img.height;
  v.scancode = 0x2F;
  big_numbers_and_letters[21] = v;

  w.sprite1 = xpm_load(w__, type, &img);
  w.width = img.width;
  w.height = img.height;
  w.scancode = 0x11;
  big_numbers_and_letters[22] = w;

  x.sprite1 = xpm_load(x__, type, &img);
  x.width = img.width;
  x.height = img.height;
  x.scancode = 0x2D;
  big_numbers_and_letters[23] = x;

  y.sprite1 = xpm_load(y__, type, &img);
  y.width = img.width;
  y.height = img.height;
  y.scancode = 0x15;
  big_numbers_and_letters[24] = y;

  z.sprite1 = xpm_load(z__, type, &img);
  z.width = img.width;
  z.height = img.height;
  z.scancode = 0x2C;
  big_numbers_and_letters[25] = z;

  travessao.sprite1 = xpm_load(travessao_, type, &img);
  travessao.width = img.width;
  travessao.height = img.height;
  travessao.scancode = 0x35;
  small_numbers[0] = travessao;

  dois_pontos.sprite1 = xpm_load(dois_pontos_, type, &img);
  dois_pontos.width = img.width;
  dois_pontos.height = img.height;
  dois_pontos.scancode = 0x34;
  small_numbers[1] = dois_pontos;

  small0.sprite1 = xpm_load(small0_, type, &img);
  small0.width = img.width;
  small0.height = img.height;
  small0.scancode = 0x0B;
  small_numbers[2] = small0;

  small1.sprite1 = xpm_load(small1_, type, &img);
  small1.width = img.width;
  small1.height = img.height;
  small1.scancode = 0x02;
  small_numbers[3] = small1;

  small2.sprite1 = xpm_load(small2_, type, &img);
  small2.width = img.width;
  small2.height = img.height;
  small2.scancode = 0x03;
  small_numbers[4] = small2;

  small3.sprite1 = xpm_load(small3_, type, &img);
  small3.width = img.width;
  small3.height = img.height;
  small3.scancode = 0x04;
  small_numbers[5] = small3;

  small4.sprite1 = xpm_load(small4_, type, &img);
  small4.width = img.width;
  small4.height = img.height;
  small4.scancode = 0x05;
  small_numbers[6] = small4;

  small5.sprite1 = xpm_load(small5_, type, &img);
  small5.width = img.width;
  small5.height = img.height;
  small5.scancode = 0x06;
  small_numbers[7] = small5;

  small6.sprite1 = xpm_load(small6_, type, &img);
  small6.width = img.width;
  small6.height = img.height;
  small6.scancode = 0x07;
  small_numbers[8] = small6;

  small7.sprite1 = xpm_load(small7_, type, &img);
  small7.width = img.width;
  small7.height = img.height;
  small7.scancode = 0x08;
  small_numbers[9] = small7;

  small8.sprite1 = xpm_load(small8_, type, &img);
  small8.width = img.width;
  small8.height = img.height;
  small8.scancode = 0x09;
  small_numbers[10] = small8;

  small9.sprite1 = xpm_load(small9_, type, &img);
  small9.width = img.width;
  small9.height = img.height;
  small9.scancode = 0x0A;
  small_numbers[11] = small9;

  big0.sprite1 = xpm_load(_big0, type, &img);
  big0.width = img.width;
  big0.height = img.height;
  big0.scancode = 0x0B;
  big_numbers_and_letters[26] = big0;

  big1.sprite1 = xpm_load(_big1, type, &img);
  big1.width = img.width;
  big1.height = img.height;
  big1.scancode = 0x02;
  big_numbers_and_letters[27] = big1;

  big2.sprite1 = xpm_load(_big2, type, &img);
  big2.width = img.width;
  big2.height = img.height;
  big2.scancode = 0x03;
  big_numbers_and_letters[28] = big2;

  big3.sprite1 = xpm_load(_big3, type, &img);
  big3.width = img.width;
  big3.height = img.height;
  big3.scancode = 0x04;
  big_numbers_and_letters[29] = big3;

  big4.sprite1 = xpm_load(_big4, type, &img);
  big4.width = img.width;
  big4.height = img.height;
  big4.scancode = 0x05;
  big_numbers_and_letters[30] = big4;

  big5.sprite1 = xpm_load(_big5, type, &img);
  big5.width = img.width;
  big5.height = img.height;
  big5.scancode = 0x06;
  big_numbers_and_letters[31] = big5;

  big6.sprite1 = xpm_load(_big6, type, &img);
  big6.width = img.width;
  big6.height = img.height;
  big6.scancode = 0x07;
  big_numbers_and_letters[32] = big6;

  big7.sprite1 = xpm_load(_big7, type, &img);
  big7.width = img.width;
  big7.height = img.height;
  big7.scancode = 0x08;
  big_numbers_and_letters[33] = big7;

  big8.sprite1 = xpm_load(_big8, type, &img);
  big8.width = img.width;
  big8.height = img.height;
  big8.scancode = 0x09;
  big_numbers_and_letters[34] = big8;

  big9.sprite1 = xpm_load(_big9, type, &img);
  big9.width = img.width;
  big9.height = img.height;
  big9.scancode = 0x0A;
  big_numbers_and_letters[35] = big9;

  point_limit.sprite1 = xpm_load(point_limit_, type, &img);
  point_limit.width = img.width;
  point_limit.height = img.height;
  point_limit.x = 390;
  point_limit.y = 325;
  GameTypePointLimit[0] = point_limit;

  title.sprite1 = xpm_load(title_, type, &img);
  title.width = img.width;
  title.height = img.height;
  title.x = 291;
  title.y = 117;
  MainMenuSprites[0] = title;
  PauseScreen[3] = title;
  WinScreen[0] = title;

  time1.sprite1 = xpm_load(time_button_, type, &img);
  time1.width = img.width;
  time1.height = img.height;
  time1.x = 101;
  time1.y = 384;

  GameType[0] = time1;

  time_limit_minutes.sprite1 = xpm_load(time_limit_seconds, type, &img);
  time_limit_minutes.width = img.width;
  time_limit_minutes.height = img.height;
  time_limit_minutes.x = 267;
  time_limit_minutes.y = 321;

  GameTypeTimeLimit[0] = time_limit_minutes;

  resume.sprite1 = xpm_load(resume_button_, type, &img);
  resume.width = img.width;
  resume.height = img.height;
  resume.x = 154;
  resume.y = 433;

  PauseScreen[0] = resume;

  res1.sprite1 = xpm_load(res_640x480, type, &img);
  res1.width = img.width;
  res1.height = img.height;
  res1.x = 320;
  res1.y = 263;

  ResolutionsMenu[0] = res1;

  res2.sprite1 = xpm_load(res_800x600, type, &img);
  res2.width = img.width;
  res2.height = img.height;
  res2.x = 320;
  res2.y = 355;

  ResolutionsMenu[1] = res2;

  res4.sprite1 = xpm_load(res_1152x864, type, &img);
  res4.width = img.width;
  res4.height = img.height;
  res4.x = 320;
  res4.y = 527;

  ResolutionsMenu[2] = res4;
  res5.sprite1 = xpm_load(res_1280x1024, type, &img);
  res5.width = img.width;
  res5.height = img.height;
  res5.x = 320;
  res5.y = 441;

  ResolutionsMenu[3] = res5;

  done.sprite1 = xpm_load(done_button_, type, &img);
  done.width = img.width;
  done.height = img.height;
  done.x = 412;
  done.y = 690;
  GameTypePointLimit[1] = done;
  GameTypeTimeLimit[1] = done;
  ResolutionsMenu[4] = done;
  HighScores[4] = done;

  endless.sprite1 = xpm_load(endless_button_, type, &img);
  endless.width = img.width;
  endless.height = img.height;
  endless.x = 383;
  endless.y = 228;
  GameType[1] = endless;

  resolution.sprite1 = xpm_load(resolution_, type, &img);
  resolution.width = img.width;
  resolution.height = img.height;
  resolution.x = 332;
  resolution.y = 48;

  ResolutionsMenu[5] = resolution;

  exit1.sprite1 = xpm_load(exit_button__, type, &img);
  exit1.width = img.width;
  exit1.height = img.height;
  exit1.x = 450;
  exit1.y = 742;
  MainMenuSprites[1] = exit1;

  game_type.sprite1 = xpm_load(game_type_, type, &img);
  game_type.width = img.width;
  game_type.height = img.height;
  game_type.x = 348;
  game_type.y = 36;
  GameType[2] = game_type;
  GameTypePointLimit[3] = game_type;
  GameTypeTimeLimit[3] = game_type;

  help.sprite1 = xpm_load(help_button_, type, &img);
  help.width = img.width;
  help.height = img.height;
  help.x = 450;
  help.y = 666;
  MainMenuSprites[2] = help;

  highscore_field.sprite1 = xpm_load(highscore_fields__, type, &img);
  highscore_field.width = img.width;
  highscore_field.height = img.height;
  highscore_field.x = 98;
  highscore_field.y = 273;
  HighScores[2] = highscore_field;

  highscores.sprite1 = xpm_load(highscore, type, &img);
  highscores.width = img.width;
  highscores.height = img.height;
  highscores.x = 295;
  highscores.y =  517;
  MainMenuSprites[3] = highscores;

  highscore_title.sprite1 = xpm_load(highscore_title_, type, &img);
  highscore_title.width = img.width;
  highscore_title.height = img.height;
  highscore_title.x = 325;
  highscore_title.y = 60;
  HighScores[0] = highscore_title;

  local.sprite1 = xpm_load(local_button_, type, &img);
  local.width = img.width;
  local.height = img.height;
  local.x = 31;
  local.y = 307;
  MainMenuSprites[4] = local;

  name_input.sprite1 = xpm_load(input_bar_name, type, &img);
  name_input.width = img.width;
  name_input.height = img.height;
  name_input.x = 185;
  name_input.y = 549;
  WinScreen[1] = name_input;

  name.sprite1 = xpm_load(name__, type, &img);
  name.width = img.width;
  name.height = img.height;
  name.x = 449;
  name.y = 229;
  HighScores[1] = name;

  new_highscore.sprite1 = xpm_load(new_highscore_, type, &img);
  new_highscore.width = img.width;
  new_highscore.height = img.height;
  new_highscore.x = 174;
  new_highscore.y = 462;
  WinScreen[2] = new_highscore;

  options.sprite1 = xpm_load(options_button_, type, &img);
  options.width = img.width;
  options.height = img.height;
  options.x = 385;
  options.y = 592;
  MainMenuSprites[5] = options;

  pause1.sprite1 = xpm_load(paused, type, &img);
  pause1.width = img.width;
  pause1.height = img.height;
  pause1.x = 411;
  pause1.y = 243;
  PauseScreen[1] = pause1;

  player1_won.sprite1 = xpm_load(player1won, type, &img);
  player1_won.width = img.width;
  player1_won.height = img.height;
  player1_won.x = 223;
  player1_won.y = 223;
  WinScreen[3] = player1_won;

  player2_won.sprite1 = xpm_load(player2won, type, &img);
  player2_won.width = img.width;
  player2_won.height = img.height;
  player2_won.x = 223;
  player2_won.y = 223;
  WinScreen[4] = player2_won;

  point_limit_input.sprite1 = xpm_load(input_time_points, type, &img);
  point_limit_input.width = img.width;
  point_limit_input.height = img.height;
  point_limit_input.x = 222;
  point_limit_input.y = 359;
  GameTypePointLimit[2] = point_limit_input;
  GameTypeTimeLimit[2] = point_limit_input;

  points.sprite1 = xpm_load(points_, type, &img);
  points.width = img.width;
  points.height = img.height;
  points.x = 654;
  points.y = 382;
  GameType[3] = points;

  quit.sprite1 = xpm_load(quit_button_, type, &img);
  quit.width = img.width;
  quit.height = img.height;
  quit.x = 368;
  quit.y = 700;
  struct Sprite quit_highscore = quit;
  quit_highscore.x = 368;
  quit_highscore.y = 700;
  struct Sprite quit_pause = quit;
  quit_pause.x = 604;
  quit_pause.y = 433;
  PauseScreen[2] = quit_pause;
  WinScreen[5] = quit;
  WinScreen[6] = quit_highscore;

  remote.sprite1 = xpm_load(remote_button_, type, &img);
  remote.width = img.width;
  remote.height = img.height;
  remote.x = 687;
  remote.y = 307;
  MainMenuSprites[6] = remote;
}


void load_mode_0x110() {
  xpm_image_t img;
  struct Animation fire_powerUp;
  struct Animation increase_powerUp;
  struct Animation decrease_powerUp;
  struct Sprite a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, travessao, dois_pontos;
  struct Sprite small0, small1, small2, small3, small4, small5, small6, small7, small8, small9;
  struct Sprite big0, big1, big2, big3, big4, big5, big6, big7, big8, big9;
  struct Sprite res1, res2, res4, res5, done, endless, exit1, game_type, help, highscore_field, highscores, highscore_title,
    local, name_input, name, new_highscore, options, pause1, player1_won, player2_won, point_limit_input, points, quit, remote,
    resolution, resume, time_limit_minutes, time1, title, point_limit, draw1;


    //HOVER//
  local.sprite1 = xpm_load(button_1152x864_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[0] = local;

  local.sprite1 = xpm_load(button_1280x1024_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[1] = local;

  local.sprite1 = xpm_load(button_640x480_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[2] = local;

  local.sprite1 = xpm_load(button_800x600_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[3] = local;

  local.sprite1 = xpm_load(button_done_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[4] = local;

  local.sprite1 = xpm_load(button_endless_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[5] = local;

  local.sprite1 = xpm_load(button_exit_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[6] = local;

  local.sprite1 = xpm_load(button_help_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[7] = local;

  local.sprite1 = xpm_load(button_highscores_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[8] = local;

  local.sprite1 = xpm_load(button_local_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[9] = local;

  local.sprite1 = xpm_load(button_options_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[10] = local;

  local.sprite1 = xpm_load(button_points_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[11] = local;

  local.sprite1 = xpm_load(button_quit_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[12] = local;

  local.sprite1 = xpm_load(button_remote_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[13] = local;

  local.sprite1 = xpm_load(button_time_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[14] = local;

  local.sprite1 = xpm_load(button_resume_hover_, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[15] = local;

  //FIRE POWERUP//

  fire_powerUp.number_of_frames = 6;
  fire_powerUp.frames[0].sprite1 = xpm_load(FIREFRAME0, type, &img);
  fire_powerUp.frames[0].width = img.width;
  fire_powerUp.frames[0].height = img.height;

  fire_powerUp.frames[1].sprite1 = xpm_load(FIREFRAME1, type, &img);
  fire_powerUp.frames[1].width = img.width;
  fire_powerUp.frames[1].height = img.height;

  fire_powerUp.frames[2].sprite1 = xpm_load(FIREFRAME2, type, &img);
  fire_powerUp.frames[2].width = img.width;
  fire_powerUp.frames[2].height = img.height;

  fire_powerUp.frames[3].sprite1 = xpm_load(FIREFRAME3, type, &img);
  fire_powerUp.frames[3].width = img.width;
  fire_powerUp.frames[3].height = img.height;

  fire_powerUp.frames[4].sprite1 = xpm_load(FIREFRAME4, type, &img);
  fire_powerUp.frames[4].width = img.width;
  fire_powerUp.frames[4].height = img.height;

  fire_powerUp.frames[5].sprite1 = xpm_load(FIREFRAME5, type, &img);
  fire_powerUp.frames[5].width = img.width;
  fire_powerUp.frames[5].height = img.height;

  Power_ups[0].animation = fire_powerUp;
  

  //INCREASE POWERUP//

  increase_powerUp.number_of_frames = 3;
  increase_powerUp.frames[0].sprite1 = xpm_load(INCREASE0, type, &img);
  increase_powerUp.frames[0].width = img.width;
  increase_powerUp.frames[0].height = img.height;

  increase_powerUp.frames[1].sprite1 = xpm_load(INCREASE1, type, &img);
  increase_powerUp.frames[1].width = img.width;
  increase_powerUp.frames[1].height = img.height;

  increase_powerUp.frames[2].sprite1 = xpm_load(INCREASE2, type, &img);
  increase_powerUp.frames[2].width = img.width;
  increase_powerUp.frames[2].height = img.height;

  Power_ups[1].animation = increase_powerUp;
  

  //DECREASE POWERUP//
  decrease_powerUp.number_of_frames = 3;

  decrease_powerUp.frames[0].sprite1 = xpm_load(DECREASE0, type, &img);
  decrease_powerUp.frames[0].width = img.width;
  decrease_powerUp.frames[0].height = img.height;

  decrease_powerUp.frames[1].sprite1 = xpm_load(DECREASE1, type, &img);
  decrease_powerUp.frames[1].width = img.width;
  decrease_powerUp.frames[1].height = img.height;

  decrease_powerUp.frames[2].sprite1 = xpm_load(DECREASE2, type, &img);
  decrease_powerUp.frames[2].width = img.width;
  decrease_powerUp.frames[2].height = img.height;

  Power_ups[2].animation = decrease_powerUp;
  

  //CURSOR//
  mouse.sprite1 = xpm_load(cursor, type, &img);
  mouse.width = img.width;
  mouse.height = img.height;
  

  //PLAYERS//
  player1.current_sprite = 0;

  player1.sprite[0].sprite1 = xpm_load(PLAYER_MED, type, &img);
  player1.sprite[0].width = img.width;
  player1.sprite[0].height = img.height;

  player1.sprite[1].sprite1 = xpm_load(PLAYER_SMALL, type, &img);
  player1.sprite[1].width = img.width;
  player1.sprite[1].height = img.height;

  player1.sprite[2].sprite1 = xpm_load(PLAYER_BIG, type, &img);
  player1.sprite[2].width = img.width;
  player1.sprite[2].height = img.height;

  player2 = player1;


  ball_.sprite.sprite1 = xpm_load(BOLL, type, &img);
  ball_.sprite.width = img.width;
  ball_.sprite.height = img.height;

  score.sprite1 = xpm_load(SCORE_, type, &img);
  score.width = img.width;
  score.height = img.height;
  score.x = vmi_p.XResolution / 2 - score.width / 2;
  score.y = 5;
  struct Sprite score1 = score;
  score1.x = 81;
  score1.y = 117;
  HighScores[3] = score1;

  draw1.sprite1 = xpm_load(draw___, type, &img);
  draw1.width = img.width;
  draw1.height = img.height;
  draw1.x = 26;
  draw1.y = 128;
  WinScreen[7] = draw1;

  a.sprite1 = xpm_load(A, type, &img);
  a.width = img.width;
  a.height = img.height;
  a.scancode = 0x1E;
  big_numbers_and_letters[0] = a;

  b.sprite1 = xpm_load(B, type, &img);
  b.width = img.width;
  b.height = img.height;
  b.scancode = 0x30;
  big_numbers_and_letters[1] = b;

  c.sprite1 = xpm_load(C, type, &img);
  c.width = img.width;
  c.height = img.height;
  c.scancode = 0x2E;
  big_numbers_and_letters[2] = c;

  d.sprite1 = xpm_load(D, type, &img);
  d.width = img.width;
  d.height = img.height;
  d.scancode = 0x20;
  big_numbers_and_letters[3] = d;

  e.sprite1 = xpm_load(E, type, &img);
  e.width = img.width;
  e.height = img.height;
  e.scancode = 0x12;
  big_numbers_and_letters[4] = e;

  f.sprite1 = xpm_load(F, type, &img);
  f.width = img.width;
  f.height = img.height;
  f.scancode = 0x21;
  big_numbers_and_letters[5] = f;

  g.sprite1 = xpm_load(G, type, &img);
  g.width = img.width;
  g.height = img.height;
  g.scancode = 0x22;
  big_numbers_and_letters[6] = g;

  h.sprite1 = xpm_load(H, type, &img);
  h.width = img.width;
  h.height = img.height;
  h.scancode = 0x23;
  big_numbers_and_letters[7] = h;

  i.sprite1 = xpm_load(I, type, &img);
  i.width = img.width;
  i.height = img.height;
  i.scancode = 0x17;
  big_numbers_and_letters[8] = i;

  j.sprite1 = xpm_load(J, type, &img);
  j.width = img.width;
  j.height = img.height;
  j.scancode = 0x24;
  big_numbers_and_letters[9] = j;

  k.sprite1 = xpm_load(K, type, &img);
  k.width = img.width;
  k.height = img.height;
  k.scancode = 0x25;
  big_numbers_and_letters[10] = k;

  l.sprite1 = xpm_load(L, type, &img);
  l.width = img.width;
  l.height = img.height;
  l.scancode = 0x26;
  big_numbers_and_letters[11] = l;

  m.sprite1 = xpm_load(M, type, &img);
  m.width = img.width;
  m.height = img.height;
  m.scancode = 0x32;
  big_numbers_and_letters[12] = m;

  n.sprite1 = xpm_load(N, type, &img);
  n.width = img.width;
  n.height = img.height;
  n.scancode = 0x31;
  big_numbers_and_letters[13] = n;

  o.sprite1 = xpm_load(O, type, &img);
  o.width = img.width;
  o.height = img.height;
  o.scancode = 0x18;
  big_numbers_and_letters[14] = o;

  p.sprite1 = xpm_load(P, type, &img);
  p.width = img.width;
  p.height = img.height;
  p.scancode = 0x19;
  big_numbers_and_letters[15] = p;

  q.sprite1 = xpm_load(Q, type, &img);
  q.width = img.width;
  q.height = img.height;
  q.scancode = 0x10;
  big_numbers_and_letters[16] = q;

  r.sprite1 = xpm_load(R, type, &img);
  r.width = img.width;
  r.height = img.height;
  r.scancode = 0x13;
  big_numbers_and_letters[17] = r;

  s.sprite1 = xpm_load(S, type, &img);
  s.width = img.width;
  s.height = img.height;
  s.scancode = 0x1f;
  big_numbers_and_letters[18] = s;

  t.sprite1 = xpm_load(T, type, &img);
  t.width = img.width;
  t.height = img.height;
  t.scancode = 0x14;
  big_numbers_and_letters[19] = t;

  u.sprite1 = xpm_load(U, type, &img);
  u.width = img.width;
  u.height = img.height;
  u.scancode = 0x16;
  big_numbers_and_letters[20] = u;

  v.sprite1 = xpm_load(V, type, &img);
  v.width = img.width;
  v.height = img.height;
  v.scancode = 0x2F;
  big_numbers_and_letters[21] = v;

  w.sprite1 = xpm_load(W, type, &img);
  w.width = img.width;
  w.height = img.height;
  w.scancode = 0x11;
  big_numbers_and_letters[22] = w;

  x.sprite1 = xpm_load(X, type, &img);
  x.width = img.width;
  x.height = img.height;
  x.scancode = 0x2D;
  big_numbers_and_letters[23] = x;

  y.sprite1 = xpm_load(Y, type, &img);
  y.width = img.width;
  y.height = img.height;
  y.scancode = 0x15;
  big_numbers_and_letters[24] = y;

  z.sprite1 = xpm_load(Z, type, &img);
  z.width = img.width;
  z.height = img.height;
  z.scancode = 0x2C;
  big_numbers_and_letters[25] = z;

  travessao.sprite1 = xpm_load(SMALLTRAVESSAO, type, &img);
  travessao.width = img.width;
  travessao.height = img.height;
  travessao.scancode = 0x35;
  small_numbers[0] = travessao;

  dois_pontos.sprite1 = xpm_load(SMALLDOISPONTOS, type, &img);
  dois_pontos.width = img.width;
  dois_pontos.height = img.height;
  dois_pontos.scancode = 0x34;
  small_numbers[1] = dois_pontos;

  small0.sprite1 = xpm_load(SMALL0, type, &img);
  small0.width = img.width;
  small0.height = img.height;
  small0.scancode = 0x0B;
  small_numbers[2] = small0;

  small1.sprite1 = xpm_load(SMALL1, type, &img);
  small1.width = img.width;
  small1.height = img.height;
  small1.scancode = 0x02;
  small_numbers[3] = small1;

  small2.sprite1 = xpm_load(SMALL2, type, &img);
  small2.width = img.width;
  small2.height = img.height;
  small2.scancode = 0x03;
  small_numbers[4] = small2;

  small3.sprite1 = xpm_load(SMALL3, type, &img);
  small3.width = img.width;
  small3.height = img.height;
  small3.scancode = 0x04;
  small_numbers[5] = small3;

  small4.sprite1 = xpm_load(SMALL4, type, &img);
  small4.width = img.width;
  small4.height = img.height;
  small4.scancode = 0x05;
  small_numbers[6] = small4;

  small5.sprite1 = xpm_load(SMALL5, type, &img);
  small5.width = img.width;
  small5.height = img.height;
  small5.scancode = 0x06;
  small_numbers[7] = small5;

  small6.sprite1 = xpm_load(SMALL6, type, &img);
  small6.width = img.width;
  small6.height = img.height;
  small6.scancode = 0x07;
  small_numbers[8] = small6;

  small7.sprite1 = xpm_load(SMALL7, type, &img);
  small7.width = img.width;
  small7.height = img.height;
  small7.scancode = 0x08;
  small_numbers[9] = small7;

  small8.sprite1 = xpm_load(SMALL8, type, &img);
  small8.width = img.width;
  small8.height = img.height;
  small8.scancode = 0x09;
  small_numbers[10] = small8;

  small9.sprite1 = xpm_load(SMALL9, type, &img);
  small9.width = img.width;
  small9.height = img.height;
  small9.scancode = 0x0A;
  small_numbers[11] = small9;

  big0.sprite1 = xpm_load(BIG0, type, &img);
  big0.width = img.width;
  big0.height = img.height;
  big0.scancode = 0x0B;
  big_numbers_and_letters[26] = big0;

  big1.sprite1 = xpm_load(BIG1, type, &img);
  big1.width = img.width;
  big1.height = img.height;
  big1.scancode = 0x02;
  big_numbers_and_letters[27] = big1;

  big2.sprite1 = xpm_load(BIG2, type, &img);
  big2.width = img.width;
  big2.height = img.height;
  big2.scancode = 0x03;
  big_numbers_and_letters[28] = big2;

  big3.sprite1 = xpm_load(BIG3, type, &img);
  big3.width = img.width;
  big3.height = img.height;
  big3.scancode = 0x04;
  big_numbers_and_letters[29] = big3;

  big4.sprite1 = xpm_load(BIG4, type, &img);
  big4.width = img.width;
  big4.height = img.height;
  big4.scancode = 0x05;
  big_numbers_and_letters[30] = big4;

  big5.sprite1 = xpm_load(BIG5, type, &img);
  big5.width = img.width;
  big5.height = img.height;
  big5.scancode = 0x06;
  big_numbers_and_letters[31] = big5;

  big6.sprite1 = xpm_load(BIG6, type, &img);
  big6.width = img.width;
  big6.height = img.height;
  big6.scancode = 0x07;
  big_numbers_and_letters[32] = big6;

  big7.sprite1 = xpm_load(BIG7, type, &img);
  big7.width = img.width;
  big7.height = img.height;
  big7.scancode = 0x08;
  big_numbers_and_letters[33] = big7;

  big8.sprite1 = xpm_load(BIG8, type, &img);
  big8.width = img.width;
  big8.height = img.height;
  big8.scancode = 0x09;
  big_numbers_and_letters[34] = big8;

  big9.sprite1 = xpm_load(BIG9, type, &img);
  big9.width = img.width;
  big9.height = img.height;
  big9.scancode = 0x0A;
  big_numbers_and_letters[35] = big9;

  point_limit.sprite1 = xpm_load(TYPETHEPOINTLIMIT, type, &img);
  point_limit.width = img.width;
  point_limit.height = img.height;
  point_limit.x = 225;
  point_limit.y = 192;
  GameTypePointLimit[0] = point_limit;

  title.sprite1 = xpm_load(TITLE_, type, &img);
  title.width = img.width;
  title.height = img.height;
  title.x = 171;
  title.y = 58;
  MainMenuSprites[0] = title;
  PauseScreen[3] = title;
  WinScreen[0] = title;

  time1.sprite1 = xpm_load(TIME_, type, &img);
  time1.width = img.width;
  time1.height = img.height;
  time1.x = 78;
  time1.y = 218;

  GameType[0] = time1;

  time_limit_minutes.sprite1 = xpm_load(TIMELIMITEINSECONDS, type, &img);
  time_limit_minutes.width = img.width;
  time_limit_minutes.height = img.height;
  time_limit_minutes.x = 163;
  time_limit_minutes.y = 185;

  GameTypeTimeLimit[0] = time_limit_minutes;

  resume.sprite1 = xpm_load(RESUME_, type, &img);
  resume.width = img.width;
  resume.height = img.height;
  resume.x = 105;
  resume.y = 245;

  PauseScreen[0] = resume;

  res1.sprite1 = xpm_load(res640x480, type, &img);
  res1.width = img.width;
  res1.height = img.height;
  res1.x = 190;
  res1.y = 151;

  ResolutionsMenu[0] = res1;

  res2.sprite1 = xpm_load(res800x600, type, &img);
  res2.width = img.width;
  res2.height = img.height;
  res2.x = 190;
  res2.y = 202;

  ResolutionsMenu[1] = res2;

  res4.sprite1 = xpm_load(res1152x864, type, &img);
  res4.width = img.width;
  res4.height = img.height;
  res4.x = 190;
  res4.y = 298;

  ResolutionsMenu[2] = res4;
  res5.sprite1 = xpm_load(res1280x1024, type, &img);
  res5.width = img.width;
  res5.height = img.height;
  res5.x = 190;
  res5.y = 250;

  ResolutionsMenu[3] = res5;

  done.sprite1 = xpm_load(DONE_, type, &img);
  done.width = img.width;
  done.height = img.height;
  done.x = 236;
  done.y = 388;
  GameTypePointLimit[1] = done;
  GameTypeTimeLimit[1] = done;
  ResolutionsMenu[4] = done;
  HighScores[4] = done;

  endless.sprite1 = xpm_load(ENDLESS_, type, &img);
  endless.width = img.width;
  endless.height = img.height;
  endless.x = 221;
  endless.y = 131;
  GameType[1] = endless;

  resolution.sprite1 = xpm_load(RESOLUTION_, type, &img);
  resolution.width = img.width;
  resolution.height = img.height;
  resolution.x = 196;
  resolution.y = 31;

  ResolutionsMenu[5] = resolution;

  exit1.sprite1 = xpm_load(EXIT_, type, &img);
  exit1.width = img.width;
  exit1.height = img.height;
  exit1.x = 255;
  exit1.y = 417;
  MainMenuSprites[1] = exit1;

  game_type.sprite1 = xpm_load(GAMETYPE_, type, &img);
  game_type.width = img.width;
  game_type.height = img.height;
  game_type.x = 204;
  game_type.y = 24;
  GameType[2] = game_type;
  GameTypePointLimit[3] = game_type;
  GameTypeTimeLimit[3] = game_type;

  help.sprite1 = xpm_load(HELP_, type, &img);
  help.width = img.width;
  help.height = img.height;
  help.x = 255;
  help.y = 375;
  MainMenuSprites[2] = help;

  highscore_field.sprite1 = xpm_load(HIGHSCOREFIELDS, type, &img);
  highscore_field.width = img.width;
  highscore_field.height = img.height;
  highscore_field.x = 80;
  highscore_field.y = 141;
  HighScores[2] = highscore_field;

  highscores.sprite1 = xpm_load(HIGHSCORES_, type, &img);
  highscores.width = img.width;
  highscores.height = img.height;
  highscores.x = 177;
  highscores.y = 291;
  MainMenuSprites[3] = highscores;

  highscore_title.sprite1 = xpm_load(HIGHSCORESTITLE, type, &img);
  highscore_title.width = img.width;
  highscore_title.height = img.height;
  highscore_title.x = 195;
  highscore_title.y = 23;
  HighScores[0] = highscore_title;

  local.sprite1 = xpm_load(LOCAL_, type, &img);
  local.width = img.width;
  local.height = img.height;
  local.x = 35;
  local.y = 175;
  MainMenuSprites[4] = local;

  name_input.sprite1 = xpm_load(BARFORNAMEINPUTWHENAHIGHSCOREHAPPENS, type, &img);
  name_input.width = img.width;
  name_input.height = img.height;
  name_input.x = 124;
  name_input.y = 331;
  WinScreen[1] = name_input;

  name.sprite1 = xpm_load(NAME_, type, &img);
  name.width = img.width;
  name.height = img.height;
  name.x = 258;
  name.y = 117;
  HighScores[1] = name;

  new_highscore.sprite1 = xpm_load(NEWHIGHSCORE, type, &img);
  new_highscore.width = img.width;
  new_highscore.height = img.height;
  new_highscore.x = 118;
  new_highscore.y = 283;
  WinScreen[2] = new_highscore;

  options.sprite1 = xpm_load(OPTIONS_, type, &img);
  options.width = img.width;
  options.height = img.height;
  options.x = 222;
  options.y = 333;
  MainMenuSprites[5] = options;

  pause1.sprite1 = xpm_load(PAUSE_, type, &img);
  pause1.width = img.width;
  pause1.height = img.height;
  pause1.x = 235;
  pause1.y = 128;
  PauseScreen[1] = pause1;

  player1_won.sprite1 = xpm_load(PLAYER1WON, type, &img);
  player1_won.width = img.width;
  player1_won.height = img.height;
  player1_won.x = 141;
  player1_won.y = 129;
  WinScreen[3] = player1_won;

  player2_won.sprite1 = xpm_load(PLAYER2WON, type, &img);
  player2_won.width = img.width;
  player2_won.height = img.height;
  player2_won.x = 141;
  player2_won.y = 129;
  WinScreen[4] = player2_won;

  point_limit_input.sprite1 = xpm_load(BARFORTIMEPOINTSINPUT, type, &img);
  point_limit_input.width = img.width;
  point_limit_input.height = img.height;
  point_limit_input.x = 140;
  point_limit_input.y = 210;
  GameTypePointLimit[2] = point_limit_input;
  GameTypeTimeLimit[2] = point_limit_input;

  points.sprite1 = xpm_load(POINTS_, type, &img);
  points.width = img.width;
  points.height = img.height;
  points.x = 359;
  points.y = 217;
  GameType[3] = points;

  quit.sprite1 = xpm_load(QUIT_, type, &img);
  quit.width = img.width;
  quit.height = img.height;
  quit.x = 222;
  quit.y = 375;
  struct Sprite quit_highscore = quit;
  quit_highscore.x = 222;
  quit_highscore.y = 375;
  struct Sprite quit_pause = quit;
  quit_pause.x = 334;
  quit_pause.y = 245;
  PauseScreen[2] = quit_pause;
  WinScreen[5] = quit;
  WinScreen[6] = quit_highscore;

  remote.sprite1 = xpm_load(REMOTE_, type, &img);
  remote.width = img.width;
  remote.height = img.height;
  remote.x = 376;
  remote.y = 175;
  MainMenuSprites[6] = remote;
}


void load_mode_0x115() {
  xpm_image_t img;
  struct Animation fire_powerUp;
  struct Animation increase_powerUp;
  struct Animation decrease_powerUp;
  struct Sprite a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, travessao, dois_pontos;
  struct Sprite small0, small1, small2, small3, small4, small5, small6, small7, small8, small9;
  struct Sprite big0, big1, big2, big3, big4, big5, big6, big7, big8, big9;
  struct Sprite res1, res2, res3, res4, done, endless, exit1, game_type, help, highscore_field, highscores, highscore_title,
    local, name_input, name, new_highscore, options, pause1, player1_won, player2_won, point_limit_input, points, quit, remote,
    resolution, resume, time_limit_minutes, time1, title, point_limit, draw1;

  //HOVER//
  local.sprite1 = xpm_load(button_1152x864_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[0] = local;

  local.sprite1 = xpm_load(button_1280x1024_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[1] = local;

  local.sprite1 = xpm_load(button_640x480_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[2] = local;

  local.sprite1 = xpm_load(button_800x600_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[3] = local;

  local.sprite1 = xpm_load(button_done_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[4] = local;

  local.sprite1 = xpm_load(button_endless_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[5] = local;

  local.sprite1 = xpm_load(button_exit_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[6] = local;

  local.sprite1 = xpm_load(button_help_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[7] = local;

  local.sprite1 = xpm_load(button_highscores_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[8] = local;

  local.sprite1 = xpm_load(button_local_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[9] = local;

  local.sprite1 = xpm_load(button_options_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[10] = local;

  local.sprite1 = xpm_load(button_points_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[11] = local;

  local.sprite1 = xpm_load(button_quit_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[12] = local;

  local.sprite1 = xpm_load(button_remote_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[13] = local;

  local.sprite1 = xpm_load(button_time_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[14] = local;

  local.sprite1 = xpm_load(button_resume_hover, type, &img);
  local.width = img.width;
  local.height = img.height;
  HoverButtons[15] = local;
  

  //FIRE POWERUP//

  fire_powerUp.number_of_frames = 6;
  fire_powerUp.frames[0].sprite1 = xpm_load(fire_frame_0, type, &img);
  fire_powerUp.frames[0].width = img.width;
  fire_powerUp.frames[0].height = img.height;

  fire_powerUp.frames[1].sprite1 = xpm_load(fire_frame_1, type, &img);
  fire_powerUp.frames[1].width = img.width;
  fire_powerUp.frames[1].height = img.height;

  fire_powerUp.frames[2].sprite1 = xpm_load(fire_frame_2, type, &img);
  fire_powerUp.frames[2].width = img.width;
  fire_powerUp.frames[2].height = img.height;

  fire_powerUp.frames[3].sprite1 = xpm_load(fire_frame_3, type, &img);
  fire_powerUp.frames[3].width = img.width;
  fire_powerUp.frames[3].height = img.height;

  fire_powerUp.frames[4].sprite1 = xpm_load(fire_frame_4, type, &img);
  fire_powerUp.frames[4].width = img.width;
  fire_powerUp.frames[4].height = img.height;

  fire_powerUp.frames[5].sprite1 = xpm_load(fire_frame_5, type, &img);
  fire_powerUp.frames[5].width = img.width;
  fire_powerUp.frames[5].height = img.height;

  Power_ups[0].animation = fire_powerUp;
  

  //INCREASE POWERUP//

  increase_powerUp.number_of_frames = 3;
  increase_powerUp.frames[0].sprite1 = xpm_load(increase_frame_0, type, &img);
  increase_powerUp.frames[0].width = img.width;
  increase_powerUp.frames[0].height = img.height;

  increase_powerUp.frames[1].sprite1 = xpm_load(increase_frame_1, type, &img);
  increase_powerUp.frames[1].width = img.width;
  increase_powerUp.frames[1].height = img.height;

  increase_powerUp.frames[2].sprite1 = xpm_load(increase_frame_2, type, &img);
  increase_powerUp.frames[2].width = img.width;
  increase_powerUp.frames[2].height = img.height;

  Power_ups[1].animation = increase_powerUp;
  

  //DECREASE POWERUP//
  decrease_powerUp.number_of_frames = 3;

  decrease_powerUp.frames[0].sprite1 = xpm_load(decrease_frame_0, type, &img);
  decrease_powerUp.frames[0].width = img.width;
  decrease_powerUp.frames[0].height = img.height;

  decrease_powerUp.frames[1].sprite1 = xpm_load(decrease_frame_1, type, &img);
  decrease_powerUp.frames[1].width = img.width;
  decrease_powerUp.frames[1].height = img.height;

  decrease_powerUp.frames[2].sprite1 = xpm_load(decrease_frame_2, type, &img);
  decrease_powerUp.frames[2].width = img.width;
  decrease_powerUp.frames[2].height = img.height;

  Power_ups[2].animation = decrease_powerUp;
  

  //CURSOR//
  mouse.sprite1 = xpm_load(cursor, type, &img);
  mouse.width = img.width;
  mouse.height = img.height;
  

  //PLAYERS//
  player1.current_sprite = 0;

  player1.sprite[0].sprite1 = xpm_load(player_med, type, &img);
  player1.sprite[0].width = img.width;
  player1.sprite[0].height = img.height;

  player1.sprite[1].sprite1 = xpm_load(player_small, type, &img);
  player1.sprite[1].width = img.width;
  player1.sprite[1].height = img.height;

  player1.sprite[2].sprite1 = xpm_load(player_big, type, &img);
  player1.sprite[2].width = img.width;
  player1.sprite[2].height = img.height;

  player2 = player1;
  

  ball_.sprite.sprite1 = xpm_load(ball, type, &img);
  ball_.sprite.width = img.width;
  ball_.sprite.height = img.height;

  score.sprite1 = xpm_load(score_subheader_, type, &img);
  score.width = img.width;
  score.height = img.height;
  score.x = vmi_p.XResolution / 2 - score.width / 2;
  score.y = 5;
  struct Sprite score1 = score;
  score1.x = 102;
  score1.y = 181;
  HighScores[3] = score1;

  draw1.sprite1 = xpm_load(draw_, type, &img);
  draw1.width = img.width;
  draw1.height = img.height;
  draw1.x = 29;
  draw1.y = 193;
  WinScreen[7] = draw1;

  a.sprite1 = xpm_load(a_, type, &img);
  a.width = img.width;
  a.height = img.height;
  a.scancode = 0x1E;
  big_numbers_and_letters[0] = a;

  b.sprite1 = xpm_load(b_, type, &img);
  b.width = img.width;
  b.height = img.height;
  b.scancode = 0x30;
  big_numbers_and_letters[1] = b;

  c.sprite1 = xpm_load(c_, type, &img);
  c.width = img.width;
  c.height = img.height;
  c.scancode = 0x2E;
  big_numbers_and_letters[2] = c;

  d.sprite1 = xpm_load(d_, type, &img);
  d.width = img.width;
  d.height = img.height;
  d.scancode = 0x20;
  big_numbers_and_letters[3] = d;

  e.sprite1 = xpm_load(e_, type, &img);
  e.width = img.width;
  e.height = img.height;
  e.scancode = 0x12;
  big_numbers_and_letters[4] = e;

  f.sprite1 = xpm_load(f_, type, &img);
  f.width = img.width;
  f.height = img.height;
  f.scancode = 0x21;
  big_numbers_and_letters[5] = f;

  g.sprite1 = xpm_load(g_, type, &img);
  g.width = img.width;
  g.height = img.height;
  g.scancode = 0x22;
  big_numbers_and_letters[6] = g;

  h.sprite1 = xpm_load(h_, type, &img);
  h.width = img.width;
  h.height = img.height;
  h.scancode = 0x23;
  big_numbers_and_letters[7] = h;

  i.sprite1 = xpm_load(i_, type, &img);
  i.width = img.width;
  i.height = img.height;
  i.scancode = 0x17;
  big_numbers_and_letters[8] = i;

  j.sprite1 = xpm_load(j_, type, &img);
  j.width = img.width;
  j.height = img.height;
  j.scancode = 0x24;
  big_numbers_and_letters[9] = j;

  k.sprite1 = xpm_load(k_, type, &img);
  k.width = img.width;
  k.height = img.height;
  k.scancode = 0x25;
  big_numbers_and_letters[10] = k;

  l.sprite1 = xpm_load(l_, type, &img);
  l.width = img.width;
  l.height = img.height;
  l.scancode = 0x26;
  big_numbers_and_letters[11] = l;

  m.sprite1 = xpm_load(m_, type, &img);
  m.width = img.width;
  m.height = img.height;
  m.scancode = 0x32;
  big_numbers_and_letters[12] = m;

  n.sprite1 = xpm_load(n_, type, &img);
  n.width = img.width;
  n.height = img.height;
  n.scancode = 0x31;
  big_numbers_and_letters[13] = n;

  o.sprite1 = xpm_load(o_, type, &img);
  o.width = img.width;
  o.height = img.height;
  o.scancode = 0x18;
  big_numbers_and_letters[14] = o;

  p.sprite1 = xpm_load(p_, type, &img);
  p.width = img.width;
  p.height = img.height;
  p.scancode = 0x19;
  big_numbers_and_letters[15] = p;

  q.sprite1 = xpm_load(q_, type, &img);
  q.width = img.width;
  q.height = img.height;
  q.scancode = 0x10;
  big_numbers_and_letters[16] = q;

  r.sprite1 = xpm_load(r_, type, &img);
  r.width = img.width;
  r.height = img.height;
  r.scancode = 0x13;
  big_numbers_and_letters[17] = r;

  s.sprite1 = xpm_load(s_, type, &img);
  s.width = img.width;
  s.height = img.height;
  s.scancode = 0x1f;
  big_numbers_and_letters[18] = s;

  t.sprite1 = xpm_load(t_, type, &img);
  t.width = img.width;
  t.height = img.height;
  t.scancode = 0x14;
  big_numbers_and_letters[19] = t;

  u.sprite1 = xpm_load(u_, type, &img);
  u.width = img.width;
  u.height = img.height;
  u.scancode = 0x16;
  big_numbers_and_letters[20] = u;

  v.sprite1 = xpm_load(v_, type, &img);
  v.width = img.width;
  v.height = img.height;
  v.scancode = 0x2F;
  big_numbers_and_letters[21] = v;

  w.sprite1 = xpm_load(w_, type, &img);
  w.width = img.width;
  w.height = img.height;
  w.scancode = 0x11;
  big_numbers_and_letters[22] = w;

  x.sprite1 = xpm_load(x_, type, &img);
  x.width = img.width;
  x.height = img.height;
  x.scancode = 0x2D;
  big_numbers_and_letters[23] = x;

  y.sprite1 = xpm_load(y_, type, &img);
  y.width = img.width;
  y.height = img.height;
  y.scancode = 0x15;
  big_numbers_and_letters[24] = y;

  z.sprite1 = xpm_load(z_, type, &img);
  z.width = img.width;
  z.height = img.height;
  z.scancode = 0x2C;
  big_numbers_and_letters[25] = z;

  travessao.sprite1 = xpm_load(travessao_small, type, &img);
  travessao.width = img.width;
  travessao.height = img.height;
  travessao.scancode = 0x35;
  small_numbers[0] = travessao;

  dois_pontos.sprite1 = xpm_load(dois_pontos_small, type, &img);
  dois_pontos.width = img.width;
  dois_pontos.height = img.height;
  dois_pontos.scancode = 0x34;
  small_numbers[1] = dois_pontos;

  small0.sprite1 = xpm_load(small_0, type, &img);
  small0.width = img.width;
  small0.height = img.height;
  small0.scancode = 0x0B;
  small_numbers[2] = small0;

  small1.sprite1 = xpm_load(small_1, type, &img);
  small1.width = img.width;
  small1.height = img.height;
  small1.scancode = 0x02;
  small_numbers[3] = small1;

  small2.sprite1 = xpm_load(small_2, type, &img);
  small2.width = img.width;
  small2.height = img.height;
  small2.scancode = 0x03;
  small_numbers[4] = small2;

  small3.sprite1 = xpm_load(small_3, type, &img);
  small3.width = img.width;
  small3.height = img.height;
  small3.scancode = 0x04;
  small_numbers[5] = small3;

  small4.sprite1 = xpm_load(small_4, type, &img);
  small4.width = img.width;
  small4.height = img.height;
  small4.scancode = 0x05;
  small_numbers[6] = small4;

  small5.sprite1 = xpm_load(small_5, type, &img);
  small5.width = img.width;
  small5.height = img.height;
  small5.scancode = 0x06;
  small_numbers[7] = small5;

  small6.sprite1 = xpm_load(small_6, type, &img);
  small6.width = img.width;
  small6.height = img.height;
  small6.scancode = 0x07;
  small_numbers[8] = small6;

  small7.sprite1 = xpm_load(small_7, type, &img);
  small7.width = img.width;
  small7.height = img.height;
  small7.scancode = 0x08;
  small_numbers[9] = small7;

  small8.sprite1 = xpm_load(small_8, type, &img);
  small8.width = img.width;
  small8.height = img.height;
  small8.scancode = 0x09;
  small_numbers[10] = small8;

  small9.sprite1 = xpm_load(small_9, type, &img);
  small9.width = img.width;
  small9.height = img.height;
  small9.scancode = 0x0A;
  small_numbers[11] = small9;

  big0.sprite1 = xpm_load(big_0, type, &img);
  big0.width = img.width;
  big0.height = img.height;
  big0.scancode = 0x0B;
  big_numbers_and_letters[26] = big0;

  big1.sprite1 = xpm_load(big_1, type, &img);
  big1.width = img.width;
  big1.height = img.height;
  big1.scancode = 0x02;
  big_numbers_and_letters[27] = big1;

  big2.sprite1 = xpm_load(big_2, type, &img);
  big2.width = img.width;
  big2.height = img.height;
  big2.scancode = 0x03;
  big_numbers_and_letters[28] = big2;

  big3.sprite1 = xpm_load(big_3, type, &img);
  big3.width = img.width;
  big3.height = img.height;
  big3.scancode = 0x04;
  big_numbers_and_letters[29] = big3;

  big4.sprite1 = xpm_load(big_4, type, &img);
  big4.width = img.width;
  big4.height = img.height;
  big4.scancode = 0x05;
  big_numbers_and_letters[30] = big4;

  big5.sprite1 = xpm_load(big_5, type, &img);
  big5.width = img.width;
  big5.height = img.height;
  big5.scancode = 0x06;
  big_numbers_and_letters[31] = big5;

  big6.sprite1 = xpm_load(big_6, type, &img);
  big6.width = img.width;
  big6.height = img.height;
  big6.scancode = 0x07;
  big_numbers_and_letters[32] = big6;

  big7.sprite1 = xpm_load(big_7, type, &img);
  big7.width = img.width;
  big7.height = img.height;
  big7.scancode = 0x08;
  big_numbers_and_letters[33] = big7;

  big8.sprite1 = xpm_load(big_8, type, &img);
  big8.width = img.width;
  big8.height = img.height;
  big8.scancode = 0x09;
  big_numbers_and_letters[34] = big8;

  big9.sprite1 = xpm_load(big_9, type, &img);
  big9.width = img.width;
  big9.height = img.height;
  big9.scancode = 0x0A;
  big_numbers_and_letters[35] = big9;

  point_limit.sprite1 = xpm_load(type_the_point_limit, type, &img);
  point_limit.width = img.width;
  point_limit.height = img.height;
  point_limit.x = 285;
  point_limit.y = 258;
  GameTypePointLimit[0] = point_limit;

  title.sprite1 = xpm_load(title_header, type, &img);
  title.width = img.width;
  title.height = img.height;
  title.x = 210;
  title.y = 106;
  MainMenuSprites[0] = title;
  PauseScreen[3] = title;
  WinScreen[0] = title;

  time1.sprite1 = xpm_load(time_button, type, &img);
  time1.width = img.width;
  time1.height = img.height;
  time1.x = 102;
  time1.y = 298;

  GameType[0] = time1;

  time_limit_minutes.sprite1 = xpm_load(time_lim_s, type, &img);
  time_limit_minutes.width = img.width;
  time_limit_minutes.height = img.height;
  time_limit_minutes.x = 207;
  time_limit_minutes.y = 258;

  GameTypeTimeLimit[0] = time_limit_minutes;

  resume.sprite1 = xpm_load(resume_button, type, &img);
  resume.width = img.width;
  resume.height = img.height;
  resume.x = 136;
  resume.y = 330;

  PauseScreen[0] = resume;

  res1.sprite1 = xpm_load(button_640x480, type, &img);
  res1.width = img.width;
  res1.height = img.height;
  res1.x = 240;
  res1.y = 219;

  ResolutionsMenu[0] = res1;

  res2.sprite1 = xpm_load(button_800x600, type, &img);
  res2.width = img.width;
  res2.height = img.height;
  res2.x = 240;
  res2.y = 279;

  ResolutionsMenu[1] = res2;

  res4.sprite1 = xpm_load(button_1152x864, type, &img);
  res4.width = img.width;
  res4.height = img.height;
  res4.x = 240;
  res4.y = 392;

  ResolutionsMenu[2] = res4;

  res3.sprite1 = xpm_load(button_1280x1024, type, &img);
  res3.width = img.width;
  res3.height = img.height;
  res3.x = 240;
  res3.y = 335;

  ResolutionsMenu[3] = res3;

  done.sprite1 = xpm_load(done_button, type, &img);
  done.width = img.width;
  done.height = img.height;
  done.x = 299;
  done.y = 498;
  GameTypePointLimit[1] = done;
  GameTypeTimeLimit[1] = done;
  ResolutionsMenu[4] = done;
  HighScores[4] = done;

  endless.sprite1 = xpm_load(endless_button, type, &img);
  endless.width = img.width;
  endless.height = img.height;
  endless.x = 280;
  endless.y = 196;
  GameType[1] = endless;

  resolution.sprite1 = xpm_load(resolution_header, type, &img);
  resolution.width = img.width;
  resolution.height = img.height;
  resolution.x = 248;
  resolution.y = 79;

  ResolutionsMenu[5] = resolution;

  exit1.sprite1 = xpm_load(exit_button_, type, &img);
  exit1.width = img.width;
  exit1.height = img.height;
  exit1.x = 323;
  exit1.y = 532;
  MainMenuSprites[1] = exit1;

  game_type.sprite1 = xpm_load(game_header, type, &img);
  game_type.width = img.width;
  game_type.height = img.height;
  game_type.x = 258;
  game_type.y = 71;
  GameType[2] = game_type;
  GameTypePointLimit[3] = game_type;
  GameTypeTimeLimit[3] = game_type;

  help.sprite1 = xpm_load(help_button, type, &img);
  help.width = img.width;
  help.height = img.height;
  help.x = 323;
  help.y = 482;
  MainMenuSprites[2] = help;

  highscore_field.sprite1 = xpm_load(highscore_fields, type, &img);
  highscore_field.width = img.width;
  highscore_field.height = img.height;
  highscore_field.x = 102;
  highscore_field.y = 207;
  HighScores[2] = highscore_field;

  highscores.sprite1 = xpm_load(highscore_button, type, &img);
  highscores.width = img.width;
  highscores.height = img.height;
  highscores.x = 224;
  highscores.y = 385;
  MainMenuSprites[3] = highscores;

  highscore_title.sprite1 = xpm_load(highscore_header, type, &img);
  highscore_title.width = img.width;
  highscore_title.height = img.height;
  highscore_title.x = 244;
  highscore_title.y = 71;
  HighScores[0] = highscore_title;

  local.sprite1 = xpm_load(local_button, type, &img);
  local.width = img.width;
  local.height = img.height;
  local.x = 47;
  local.y = 248;
  MainMenuSprites[4] = local;

  name_input.sprite1 = xpm_load(highscore_input_name_bar, type, &img);
  name_input.width = img.width;
  name_input.height = img.height;
  name_input.x = 155;
  name_input.y = 406;
  WinScreen[1] = name_input;

  name.sprite1 = xpm_load(name_subheader, type, &img);
  name.width = img.width;
  name.height = img.height;
  name.x = 322;
  name.y = 181;
  HighScores[1] = name;

  new_highscore.sprite1 = xpm_load(new_highcore_subheader, type, &img);
  new_highscore.width = img.width;
  new_highscore.height = img.height;
  new_highscore.x = 148;
  new_highscore.y = 349;
  WinScreen[2] = new_highscore;

  options.sprite1 = xpm_load(options_button, type, &img);
  options.width = img.width;
  options.height = img.height;
  options.x = 281;
  options.y = 434;
  MainMenuSprites[5] = options;

  pause1.sprite1 = xpm_load(pause_subheader, type, &img);
  pause1.width = img.width;
  pause1.height = img.height;
  pause1.x = 298;
  pause1.y = 193;
  PauseScreen[1] = pause1;

  player1_won.sprite1 = xpm_load(player_1_won_subheader, type, &img);
  player1_won.width = img.width;
  player1_won.height = img.height;
  player1_won.x = 179;
  player1_won.y = 193;
  WinScreen[3] = player1_won;

  player2_won.sprite1 = xpm_load(player_2_won_subheader, type, &img);
  player2_won.width = img.width;
  player2_won.height = img.height;
  player2_won.x = 179;
  player2_won.y = 193;
  WinScreen[4] = player2_won;

  point_limit_input.sprite1 = xpm_load(point_and_time_limit_input_bar, type, &img);
  point_limit_input.width = img.width;
  point_limit_input.height = img.height;
  point_limit_input.x = 178;
  point_limit_input.y = 282;
  GameTypePointLimit[2] = point_limit_input;
  GameTypeTimeLimit[2] = point_limit_input;

  points.sprite1 = xpm_load(points_button, type, &img);
  points.width = img.width;
  points.height = img.height;
  points.x = 451;
  points.y = 297;
  GameType[3] = points;

  quit.sprite1 = xpm_load(quit_button, type, &img);
  quit.width = img.width;
  quit.height = img.height;
  quit.x = 280;
  quit.y = 330;
  struct Sprite quit_highscore = quit;
  quit_highscore.x = 283;
  quit_highscore.y = 480;
  struct Sprite quit_pause = quit;
  quit_pause.x = 420;
  quit_pause.y = 330;
  PauseScreen[2] = quit_pause;
  WinScreen[5] = quit;
  WinScreen[6] = quit_highscore;

  remote.sprite1 = xpm_load(remote_button, type, &img);
  remote.width = img.width;
  remote.height = img.height;
  remote.x = 473;
  remote.y = 248;
  MainMenuSprites[6] = remote;
}

