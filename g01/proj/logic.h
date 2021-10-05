#ifndef LOGIC_H
#define LOGIC_H

#include "rtc.h"
#include "animations.h"
#include <stdbool.h>

/// <summary>
/// Struct which represents a player
/// </summary>
struct Player{
    /// <summary>
    /// y speed of the player
    /// </summary>
    int y_speed;
    /// <summary>
    /// score of the player
    /// </summary>
    int score;
    /// <summary>
    /// sprites for the player, it has a small, medium and big sprite because of poweups
    /// </summary>
    struct Sprite sprite[3];
    /// <summary>
    /// Sprite being used currently
    /// </summary>
    int current_sprite;
};

/// <summary>
/// Struct which represents a ball
/// </summary>
struct Ball{
    /// <summary>
    /// speed in x
    /// </summary>
    int x_speed;
    /// <summary>
    /// speed in y
    /// </summary>
    int y_speed;
    /// <summary>
    /// total speed
    /// </summary>
    float ball_speed;
    /// <summary>
    /// sprite of the ball
    /// </summary>
    struct Sprite sprite;
};

/// <summary>
/// Handles the movement of the ball.
/// If a player scores resets the ball.
/// If the ball hits the upper or lower bounds, it makes the ball bounce off of it.
/// Checks for collisiond with the players and if they happen it waits a few frames to avoid accidental clipping.
/// Stops the ball from going out of bounds.
/// </summary>
/// <param name="waiting_frames"></param> frames to wait after a colision
void handle_ball_movement(int* waiting_frames);

/// <summary>
/// Places the ball in the center of the screen and resets its speed
/// </summary>
void reset_ball();

/// <summary>
/// Places players in their staring positions and resets their speed
/// </summary>
void initialize_players();

/// <summary>
/// Handles left clicks to menu buttons.
/// The action will depend on the current menu and the button clickes, for example id in the resolutions menu it might allow the user to change the menu's resolution
/// if in the main menu it might allow the user to chose a game mode, see the highscores or exit the aplication.
/// </summary>
/// <param name="A"></param> array of the current menu
/// <param name="size"></param> size of the current menu
void handle_menu_events(struct Sprite A[], unsigned int size);

/// <summary>
/// Checks if two menus are the same
/// </summary>
/// <param name="A"></param> a menu to compare
/// <param name="B"></param> a menu to compare
/// <param name="size"></param> the size of the menu
/// <returns> true if they are the same menu, false otherwise </returns>
bool checkIfEqual(struct Sprite A[], struct Sprite B[], unsigned int size);

/// <summary>
/// returns the index of the button that was clicked
/// </summary>
/// <param name="buttons"></param> current menu
/// <param name="size"></param> size of the current menu
/// <returns> the button index if the mouse was over the button, -1 otherwise </returns>
int ButtonClicked(struct Sprite buttons[], unsigned int size);

/// <summary>
/// Puts the menu in the arguments in the current menu
/// </summary>
/// <param name="A"></param> next menu
/// <param name="size"></param> size of the next menu
void copyArray(struct Sprite A[],unsigned int size);

/// <summary>
/// Checks for collisions between the balls and the player specifiyed
/// </summary>
/// <param name="player"></param> player to check for colisions
/// <returns> true if the ball colides with the player, false otherwise </returns>
bool colision(struct Player* player);

/// <summary>
/// Checks if the pixel in the position (x,y) is part of the ball
/// </summary>
/// <param name="x"></param> position x of the pixel
/// <param name="y"></param> psotion y of the pixel
/// <returns> true if it is, false otherwise </returns>
bool is_colliding(int x, int y);

/// <summary>
/// Saves ball from overlaping with palyer 1:
/// if the player drags the ball by moving while it is on top or on the bottom of the player
/// if the ball speed would lead it to clip through the player before collision could be checked
/// </summary>
/// <returns> true if the player was going to overlap, false otherwise </returns>
bool overlap_save_p1();

/// <summary>
/// Saves ball from overlaping with palyer 2:
/// if the player drags the ball by moving while it is on top or on the bottom of the player
/// if the ball speed would lead it to clip through the player before collision could be checked
/// </summary>
/// <returns> true if the player was going to overlap, false otherwise </returns>
bool overlap_save_p2();

/// <summary>
/// Creates a cursor in the center of the screen
/// </summary>
void create_mouse();

/// <summary>
/// Reads the last highscore from the highscore.txt file along with the players name, date and time of the highscore
/// </summary>
void read_highscore_from_file();

/// <summary>
/// Writes the new highscore to highscore.txt file along with the players name, date and time of the highscore
/// </summary>
void write_highscore_to_file();

/// <summary>
/// Updates the score values at the top of the screen
/// </summary>
void update_score();

/// <summary>
/// Allows the playr to write in real time.
/// Accepts number and letters depending the field where the player is writting
/// </summary>
void realTimeWritting();

/// <summary>
/// Uses the mouse packets to move player 2.
/// </summary>
void control_player2();

/// <summary>
/// Uses keyboard scancodes to mode player 1.
/// </summary>
void control_player1();

/// <summary>
/// Checks if the user pressed de 'q' key and brings up the pause menu
/// </summary>
void checkIfPaused();

/// <summary>
/// Checks if a button is being hovered and if so draws a different sprite from the usuaç
/// </summary>
/// <param name="A"></param> current menu
/// <param name="size"></param> size of the current menu
void handleHoverMenu(struct Sprite A[], unsigned int size);

#endif
