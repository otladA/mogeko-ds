#pragma once

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

typedef enum{
    LEFT = 0,
    CENTER = 127,
    RIGHT = 255
} Panning;

typedef enum{
    SFX,
    SONG
} AudioType;

typedef struct{
    mm_sound_effect sound;
    mm_sfxhand handler;
} Sfx;

typedef struct{
    bool loop;
} Song;

typedef struct{
    AudioType type; 
    mm_word id;

    union{
        Sfx sfx;
        Song song;
    };

} Audio;

void play_song(mm_word song_id, bool loop);
void play_sfx(mm_word sfx_id, int volume, Panning panning);
void audio_cleanup();