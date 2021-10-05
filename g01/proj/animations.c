#include "animations.h"
#include "video_gr.h"

extern int counter_timer;
extern struct Player player1, player2;

void handle_animation(struct Animation* anim,int ticks_to_wait, bool reversed){
    if( (anim->prev_frame_counter + ticks_to_wait) <= counter_timer ){
        anim->prev_frame_counter = counter_timer;
        erase_sprite(anim->frames[anim->current_frame]);
        if(reversed)
            anim->current_frame = anim->current_frame - 1;
        else 
            anim->current_frame = (anim->current_frame + 1) % anim->number_of_frames;
        
        draw_sprite(anim->frames[anim->current_frame]);
    }
}

void set_animation_initial_frame(struct Animation* anim, int counter){
    anim->prev_frame_counter = counter;
}
