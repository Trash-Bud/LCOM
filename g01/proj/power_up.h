#ifndef POWER_UP_H
#define POWER_UP_H

#include <stdbool.h>
#include "animations.h"

/// <summary>
/// Struct which represents a power up
/// </summary>
struct PowerUp{
    /// <summary>
    /// Animation of the powerup
    /// </summary>
    struct Animation animation;
    /// <summary>
    /// State of the power up
    /// </summary>
    bool active;
    /// <summary>
    /// true if the powerup is being rendered on screen
    /// </summary>
    bool render;
    /// <summary>
    /// counter when the power up is spawned so that the animation can be played with the correct frame rate
    /// </summary>
    int counter_initial;
    /// <summary>
    /// function that handles what happens when a powerup is activated
    /// </summary>
    void (*func)();
};


/// <summary>
/// Has a certain chance to spawn a powerup
/// </summary>
/// <returns> the index of the powerUp if it is spawned, -1 otherwise </returns>
int handlePowerUpSpawn();

/// <summary>
/// initializes power ups and the funtion that handles them
/// </summary>
void initialize_powerUps();

/// <summary>
/// function that handles the powerup which increases the ball's speed
/// </summary>
void ball_speed_power_up_function();

/// <summary>
/// function that handles the poweup which increases the player size
/// </summary>
void increase_player_size_power_up_function();

/// <summary>
/// function that handles the poweup which decreases the player size
/// </summary>
void decrease_player_size_power_up_function();

/// <summary>
/// Function which erases the power up when it is collected and calls the function to handle it.
/// </summary>
/// <param name="power_up"></param> power up caught
void collect_power_up(struct PowerUp* power_up);

/// <summary>
/// Ends a power up's effect
/// </summary>
void handleRemovePowerUp();

/// <summary>
/// Checks if the ball and the power up is colling
/// </summary>
/// <param name="power_up"></param> power up to check
/// <returns> true if they collide, false otherwise </returns>
bool is_ball_colliding_with_powerUp(struct PowerUp* power_up);

/// <summary>
/// Deactivates all powerups and their effects
/// </summary>
void deactivate_all_power_up();

#endif
