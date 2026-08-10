#include "dialog.h"
#include "audio.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Dialog *dialog_create(int line_count){
    Dialog *d = (Dialog*)malloc(sizeof(Dialog));

    d->line_count = line_count;
    d->current_line = 0;
    d->finished = 0;
    d->is_open = 0;
    d->typing_progress = 0;
    d->typing_timer = 0;
    d->text_fully_displayed = 0;
    d->typing_speed = TYPING_SPEED;
    d->typing_sound_id = -1;

    return d;
}

void dialog_add_line(Dialog *dialog, const char* speaker, const char* text, CharacterId speaker_id){
    if (dialog->current_line >= MAX_LINES_PER_DIALOG) return;

    dialog->lines[dialog->current_line].speaker = speaker;
    dialog->lines[dialog->current_line].text = text;
    dialog->lines[dialog->current_line].speaker_id = speaker_id;
    dialog->current_line++;
}

void dialog_open(Dialog *dialog, CharacterPortraitId char_id){
    if (dialog->is_open) return;

    dialog->is_open = 1;
    dialog->current_line = 0;
    dialog->typing_progress = 0;
    dialog->typing_timer = 0;
    dialog->text_fully_displayed = 0;

    consoleInit(&dialog->console, 0, BgType_Text4bpp, BgSize_T_256x256, 24, 4, false, true);

    Image *portrait = get_char_portrait(char_id);
    dmaCopy(portrait->palette_data, BG_PALETTE_SUB + portrait->palette_offset, portrait->palette_len);

    windowEnableSub(WINDOW_0);
    windowSetBoundsSub(WINDOW_0, 85, 120, 248, 176);

    int text_bg = dialog->console.bgId;
    bgSetScroll(text_bg, 160, 140);
    bgUpdate();
    bgWindowEnable(text_bg, WINDOW_0);
    bgWindowDisable(text_bg, WINDOW_OUT);
    bgWindowEnable(get_img_id(portrait), WINDOW_OUT);
    bgWindowDisable(get_img_id(portrait), WINDOW_0);

    consoleSelect(&dialog->console);
    iprintf("\x1b[2J");     // clean
}

void dialog_update(Dialog *dialog){
    if (!dialog->is_open || dialog->current_line >= dialog->line_count) return;

    DialogLine *line = &dialog->lines[dialog->current_line];
    int text_len = strlen(line->text);

    if (dialog->typing_progress < text_len){
        dialog->typing_timer++;

        if (dialog->typing_timer >= dialog->typing_speed){
            dialog->typing_timer = 0;
            dialog->typing_progress++;

            if (dialog->typing_sound_id >= 0){
                play_sfx(dialog->typing_sound_id, 64, CENTER);
            }
        }

        if (keysDown() &KEY_A){
            dialog->typing_progress = text_len;
            dialog->text_fully_displayed = 1;
        }

    } else{
        dialog->text_fully_displayed = 1;
    }

    if (dialog->text_fully_displayed && keysDown() &KEY_A){
        dialog->current_line++;
        dialog->typing_progress = 0;
        dialog->typing_timer = 0;
        dialog->text_fully_displayed = 0;

        if(dialog->current_line >= dialog->line_count){
            dialog->finished = 1;
        } else{
            dialog_render(dialog);
        }
    } else{
        dialog_render(dialog);
    }
}

void dialog_render(Dialog *dialog){
    if (!dialog->is_open || dialog->current_line >= dialog->line_count) return;

    DialogLine *line = &dialog->lines[dialog->current_line];
    consoleSelect(&dialog->console);

    // Clean
    iprintf("\x1b[2J");
    
    // Print character name
    iprintf("\x1b[1;1H%s\n\n", line->speaker);
    
    // Print partial text
    char partial_text[512];
    strncpy(partial_text, line->text, dialog->typing_progress);
    partial_text[dialog->typing_progress] = '\0';

    int cursor_y = 3;
    int line_char_count = 0;

    for (int i = 0; partial_text[i] != '\0' && cursor_y < 3 + MAX_TEXT_LINES; i++){
        if (partial_text[i] == '\n'){
            iprintf("\n");
            cursor_y++;
            line_char_count = 0;
            continue;
        }

        if (line_char_count >= MAX_CHARS_PER_LINE){
            printf("\n");
            cursor_y++;
            line_char_count = 0;

            if (cursor_y >= 3 + MAX_TEXT_LINES){
                break;
            }
        }

        iprintf("%c", partial_text[i]);
        line_char_count++;
    }
    
    // Indicates there's more text (press A to continue)
    // if (dialog->text_fully_displayed){
    //     iprintf("\x1b[6;1H[A]");
    // }

}

int dialog_is_finished(Dialog *dialog){
    return dialog->finished;
}

void dialog_close(Dialog *dialog){
    if (!dialog->is_open) return;

    dialog->is_open = 0;
    windowDisableSub(WINDOW_0);
    iprintf("\x1b[2J");
}

void dialog_set_typing_speed(Dialog *dialog, int speed){
    dialog->typing_speed = speed;
}

void dialog_set_typing_sound(Dialog *dialog, int sound_id){
    dialog->typing_sound_id = sound_id;
}
void dialog_cleanup(Dialog *dialog){
    dialog_close(dialog);
    free(dialog);
}