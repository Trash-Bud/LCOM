#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <lcom/lcf.h>

/// <summary>
/// Struct which has all the information about a sprite.
/// </summary>
struct Sprite {
  /// <summary>
  /// Adress of the first byte of a sprite
  /// </summary>
  uint8_t *sprite1;
  /// <summary>
  /// Width of the sprite
  /// </summary>
  int width;
  /// <summary>
  /// Height of the sprite
  /// </summary>
  int height;
  /// <summary>
  /// Position in x of the left top corner of the sprite
  /// </summary>
  int x;
  /// <summary>
  /// Position in y of the left top corner of the sprite
  /// </summary>
  int y;
  /// <summary>
  /// If the sprite is a letter or number then this is the scancode of the letter, otherwise it goes unused
  /// </summary>
  uint8_t scancode;
};

/// <summary>
/// Struct which contains an animation
/// </summary>
struct Animation {
  /// <summary>
  /// Frames of the animations (can have a maximum of 6)
  /// </summary>
  struct Sprite frames[6];
  /// <summary>
  /// Number of frames of the animation
  /// </summary>
  int number_of_frames;
  /// <summary>
  /// Stores the timer counter value of when the animation was called so that it can be played at the correct frame rate
  /// </summary>
  int prev_frame_counter;
  /// <summary>
  /// Stores the current frame
  /// </summary>
  int current_frame;
};

/// <summary>
/// Animates de animation to a specific frame rate, can also play the animation in reverse
/// </summary>
/// <param name="anim"></param> animation to play
/// <param name="ticks_to_wait"></param> ticks_to_way equals should be equal to the frequency of the timer divided by the intended frame rate.
/// <param name="reversed"></param> true if the animation is to play in reverse, false otherwise
void handle_animation(struct Animation* anim,int ticks_to_wait, bool reversed);

/// <summary>
/// Sets the previous frame as the value of the current timer counter when the animation starts playing so that it can be drawn ate the correct frame rate
/// </summary>
/// <param name="anim"></param>
/// <param name="counter"></param>
void set_animation_initial_frame(struct Animation* anim, int counter);


#endif
