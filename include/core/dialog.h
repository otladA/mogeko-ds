#pragma once

#include <nds.h>
#include "characters.h"

#define MAX_DIALOGS 64
#define MAX_LINES_PER_DIALOG 20
#define MAX_DIALOGUE_LENGTH 256
#define MAX_CHARS_PER_LINE 19
#define MAX_TEXT_LINES 3

#define TYPING_SPEED 2;

typedef struct{
    const char* speaker;
    const char* text;
    CharacterId speaker_id;
} DialogLine;

typedef struct{
    PrintConsole console;
    DialogLine lines[MAX_LINES_PER_DIALOG];
    int line_count;
    int current_line;
    int finished;
    int is_open;

    int typing_progress;
    int typing_timer;
    int text_fully_displayed;
    int typing_speed;
    int typing_sound_id;
} Dialog;

Dialog *dialog_create(int line_count);
void dialog_add_line(Dialog *dialog, const char* speaker, const char* text, CharacterId speaker_id);
void dialog_open(Dialog *dialog, CharacterPortraitId char_id);
void dialog_update(Dialog *dialog);
void dialog_render(Dialog *dialog);
int dialog_is_finished(Dialog *dialog);
void dialog_close(Dialog *dialog);
void dialog_cleanup(Dialog *dialog);
void dialog_set_typing_speed(Dialog *dialog, int speed);
void dialog_set_typing_sound(Dialog *dialog, int sound_id);