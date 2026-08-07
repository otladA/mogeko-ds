#include "audio.h"

void play_song(mm_word song_id, bool loop){
    // Stop any music currently playing to avoid overlapping
    mmStop();

    mmLoad(song_id);
	mmStart(song_id, loop ? MM_PLAY_LOOP : MM_PLAY_ONCE);
}