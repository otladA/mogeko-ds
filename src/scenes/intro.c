#include <nds.h>

#include "intro.h"
#include "graphics.h"
#include "audio.h"
#include "backgrounds.h"
#include "characters.h"
#include "dialog.h"

static Dialog* intro_dialog = NULL;
typedef enum{
    INTRO_LOGO,
    INTRO_WARNING,
    INTRO_STORY,
    INTRO_DIALOG,
    INTRO_FADE_OUT,
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
                img_transition(SUB, (get_char_portrait(YONAKA_IDLE)), 64);
                play_song(MOD_MAIN_THEME, true);

                state->state = INTRO_STORY;
                state->timer = 0;
            }

            break;

        case INTRO_STORY:
            if (state->timer > 60){

                if (!intro_dialog){
                    intro_dialog = dialog_create(18);

                    dialog_add_line(intro_dialog, "???", "Hey. Can't sleep?", YONAKA);
                    dialog_add_line(intro_dialog, "???", ".....", YONAKA);
                    dialog_add_line(intro_dialog, "???", "Did you drink your medicine?", YONAKA);
                    dialog_add_line(intro_dialog, "???", ".....", YONAKA);
                    dialog_add_line(intro_dialog, "???", "...I see.", YONAKA);
                    dialog_add_line(intro_dialog, "???", ".....", YONAKA);
                    dialog_add_line(intro_dialog, "???", "It's okay. I'm here.", YONAKA);
                    dialog_add_line(intro_dialog, "???", "...I hope you get better soon.", YONAKA);
                    dialog_add_line(intro_dialog, "???", ".....", YONAKA);
                    dialog_add_line(intro_dialog, "???", "...Oh, I know.", YONAKA);
                    dialog_add_line(intro_dialog, "???", "...I'll read you a story today.", YONAKA);
                    dialog_add_line(intro_dialog, "???", "What kind, you ask?", YONAKA);
                    dialog_add_line(intro_dialog, "???", "It's very amusing, sad... violent, pervy.", YONAKA);
                    dialog_add_line(intro_dialog, "???", "...That kind of story.", YONAKA);
                    dialog_add_line(intro_dialog, "???", "I think you'll enjoy it, too.", YONAKA);
                    dialog_add_line(intro_dialog, "???", ".....", YONAKA);
                    dialog_add_line(intro_dialog, "???", ".....", YONAKA);
                    dialog_add_line(intro_dialog, "???", "Well then, let's begin.", YONAKA);

                    dialog_open(intro_dialog, YONAKA_IDLE);
                    dialog_render(intro_dialog);
                }

                state->state = INTRO_DIALOG;
                state->timer = 0;
            }

            break;
        
        case INTRO_DIALOG:
            dialog_update(intro_dialog);

            if (dialog_is_finished(intro_dialog)){
                dialog_close(intro_dialog);
                state->state = INTRO_FADE_OUT;
                state->timer = 0;
            }

            break;

        case INTRO_FADE_OUT:
            if (state->timer > 120 && dialog_is_finished(intro_dialog)){
                img_fade_out(BOTH, 3000, 64);
                setBrightness(BOTH, -16);
                state->finished = 1;
                state->state = INTRO_COMPLETE;
            }
            
            break;
        case INTRO_COMPLETE:
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
}