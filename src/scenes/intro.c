#include <nds.h>

#include <intro.h>
#include <graphics.h>
#include <audio.h>
#include <backgrounds.h>
#include <char_portraits.h>

typedef enum{
    INTRO_FADE_IN,
    INTRO_LOGO,
    INTRO_WARNING,
    INTRO_STORY,
    INTRO_FADE_OUT,
    INTRO_COMPLETE
} IntroPhase;

static IntroState intro_state = {0};

IntroState *intro_init(void){
    intro_state.state = INTRO_FADE_IN;
    intro_state.timer = 0;
    intro_state.finished = 0;

    img_load(get_background(BG_FUNAMUSEA_LOGO));
    img_fade_in(MAIN, 3000, 64);

    return &intro_state;
}

void intro_update(IntroState *state){
    state->timer++;

    switch(state->state){
        case INTRO_FADE_IN:
            if (state->timer > 60){
                state->state = INTRO_LOGO;
                state->timer = 0;
            } 

            break;

        case INTRO_LOGO:
            if (state->timer > 120){
                img_transition(MAIN, get_background(BG_MOGEKO_WARNING), 64);
                play_sfx(SFX_MOGEKO_WARNING, 255, CENTER);
                state->state = INTRO_WARNING;
                state->timer = 0;
            }

            break;

        case INTRO_WARNING:
            if (state->timer > 650 || (keysDown() &KEY_A)){
                audio_cleanup();
                img_transition(MAIN, get_background(BG_MOGEBED), 64);
                img_transition(SUB, (get_char_portrait(YONAKA_IDLE)), 64);
                play_song(MOD_MAIN_THEME, true);
                state->state = INTRO_STORY;
                state->timer = 0;
            }

            break;

        case INTRO_STORY:
            if (state->timer > 600 || (keysDown() &KEY_A)){
                img_fade_out(BOTH, 3000, 64);
                state->state = INTRO_FADE_OUT;
                state->timer = 0;
            }

            break;
        
        default:
            break;
    }
}

int intro_is_finished(IntroState *state){
    return state->finished;
}

void intro_cleanup(IntroState *state){
    audio_cleanup();
}