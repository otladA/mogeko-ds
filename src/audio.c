#include "audio.h"

void play_song(mm_word song_id, bool loop){
    // Stop any music currently playing to avoid overlapping
    mmStop();

    mmLoad(song_id);
	mmStart(song_id, loop ? MM_PLAY_LOOP : MM_PLAY_ONCE);
}

void play_sfx(mm_word sfx_id, int volume, Panning panning){
    mmLoadEffect(sfx_id);

    mm_sound_effect sfx = {
        { sfx_id },
        (int)(1.0f * (1<<10)),  // rate
        0,                      // handle
        volume,                 
        panning,
    };

    mmEffectEx(&sfx);
}