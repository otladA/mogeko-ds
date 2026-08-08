#pragma once

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

typedef enum{
    LEFT = 0,
    CENTER = 127,
    RIGHT = 255
} Panning;

void play_song(mm_word song_id, bool loop);

void play_sfx(mm_word sfx_id, int volume, Panning panning);