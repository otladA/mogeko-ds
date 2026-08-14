#include <nds.h>

#include "intro.h"
#include "graphics.h"
#include "audio.h"
#include "backgrounds.h"
#include "characters.h"
#include "dialog.h"

static Dialog* intro_dialog = NULL;
static Dialog* intro_dialog2 = NULL;
int has_played = 0;
typedef enum{
    INTRO_LOGO,
    INTRO_WARNING,
    INTRO_STORY,
    INTRO_STORY_FADE_OUT,
    INTRO_COMPLETE
} IntroPhase;

static IntroState intro_state = {0};

IntroState *intro_init(void){
    intro_state.state = INTRO_LOGO;
    intro_state.timer = 0;
    intro_state.finished = 0;

    img_load(get_background(BG_FUNAMUSEA_LOGO));
    img_fade_in(MAIN, 3000, 64);

    return &intro_state;
}

void intro_update(IntroState *state){
    state->timer++;

    switch(state->state){
        case INTRO_LOGO:
            if (state->timer > 120 || (keysDown() &KEY_START)){
                img_transition(MAIN, get_background(BG_MOGEKO_WARNING), 64);
                play_sfx(SFX_MOGEKO_WARNING, 255, CENTER);
                state->state = INTRO_WARNING;
                state->timer = 0;
            }

            break;

        case INTRO_WARNING:
            if (state->timer > 650 || (keysDown() &KEY_START)){
                audio_cleanup();
                img_transition(MAIN, get_background(BG_MOGEBED), 64);
                img_transition(SUB, (get_char_portrait(STRANGE_MOGE_IDLE)), 64);

                state->state = INTRO_STORY;
                state->timer = 0;
            }

            break;

        case INTRO_STORY:
            if (state->timer > 60){

                if (!intro_dialog){
                    intro_dialog = dialog_create(18);

                    dialog_add_line(intro_dialog, "???", "Hey. Can't sleep?", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", ".....", STRANGE_MOGEKO + 1);
                    dialog_add_line(intro_dialog, "???", "Did you drink your medicine?", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", ".....", STRANGE_MOGEKO + 1);
                    dialog_add_line(intro_dialog, "???", "...I see.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", ".....", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "It's okay. I'm here.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "...I hope you get better soon.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", ".....", STRANGE_MOGEKO + 1);
                    dialog_add_line(intro_dialog, "???", "...Oh, I know.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "...I'll read you a story today.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "What kind, you ask?", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "It's very amusing, sad... violent, pervy.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "...That kind of story.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", "I think you'll enjoy it, too.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog, "???", ".....", STRANGE_MOGEKO + 1);
                    dialog_add_line(intro_dialog, "???", ".....", STRANGE_MOGEKO + 1);
                    dialog_add_line(intro_dialog, "???", "Well then, let's begin.", STRANGE_MOGEKO);

                    dialog_open(intro_dialog, STRANGE_MOGE_IDLE);
                    dialog_render(intro_dialog);
                }

                dialog_update(intro_dialog);

                if (dialog_is_finished(intro_dialog)){
                    dialog_cleanup(intro_dialog);
                    intro_dialog = NULL;
                    state->state = INTRO_STORY_FADE_OUT;
                    state->timer = 0;
                }
            }

            break;

        case INTRO_STORY_FADE_OUT:
            if (has_played == 0){
                img_fade_out(MAIN, 3000, 64);
                play_sfx(SFX_PAPER01, 255, CENTER);
                has_played = 1;
            }

            if (state->timer > 120){
                if (!intro_dialog2){
                    intro_dialog2 = dialog_create(3);

                    play_sfx(SFX_ONEPOINT7, 255, CENTER);

                    dialog_add_line(intro_dialog2, "???", "Once upon a time, there was a high schooler", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog2, "???", "Her name was Yonaka.", STRANGE_MOGEKO);
                    dialog_add_line(intro_dialog2, "???", "One day, she took the train...", STRANGE_MOGEKO);

                    dialog_open(intro_dialog2, STRANGE_MOGE_IDLE);
                    dialog_render(intro_dialog2);
                }

                dialog_update(intro_dialog2);
            
                if (dialog_is_finished(intro_dialog2)){
                    img_fade_out(SUB, 3000, 64);
                    dialog_cleanup(intro_dialog2);
                    state->state = INTRO_COMPLETE;
                    state->timer = 0;
                }
            }
            
            break;

        case INTRO_COMPLETE:
            state->finished = 1;
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
    dialog_cleanup(intro_dialog);
    dialog_cleanup(intro_dialog2);
}