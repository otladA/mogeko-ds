#include "audio.h"

static Audio current;

/**
 * @brief Loads and plays a .MOD Music Track.
 * 
 * Stops any currently playing music before starting the new track
 * to prevent overlapping playback.
 * 
 * @param song_id Identifier of the .MOD song to play (from soundbank).
 * @param loop If true, the song loops indefinitely; if false, plays once.
 */
void play_song(mm_word song_id, bool loop){
    // Stop any music currently playing to avoid overlapping
    mmStop();

    mmLoad(song_id);
	mmStart(song_id, loop ? MM_PLAY_LOOP : MM_PLAY_ONCE);

    current = (Audio){
        .type = SONG,
        .id = song_id,
        .song.loop = loop
    };
}

/**
 * @brief Plays a short .WAV sound effect.
 * 
 * Loads the effect on first use and reuses the handler for subsequent
 * plays of the same effect. Only one SFX is tracked at a time.
 * 
 * @param sfx_id    Identifier of the .WAV effect to play (from soundbank).
 * 
 * @param volume Playback volume. Range: 0 (silent) to 255 (max).
 * @param panning Stereo panning position. Accepts LEFT, CENTER, or RIGHT
 * (defined in Panning enum).
 */
void play_sfx(mm_word sfx_id, int volume, Panning panning){
    if (current.type != SFX || current.id != sfx_id){
        mmLoadEffect(sfx_id);
    }

    mm_sound_effect sfx = {
        { sfx_id },
        (int)(1.0f * (1<<10)),  // rate
        (current.type == SFX) ? current.sfx.handler : 0, // handle
        volume,
        panning,
    };

    current.sfx.handler = mmEffectEx(&sfx);
    current.type = SFX;
    current.id = sfx_id;
    current.sfx.sound = sfx;

}

void audio_cleanup(void){
    switch (current.type){
    case SONG:
        mmStop();
        mmUnload(current.id);
        break;
    
    case SFX:
        mmEffectCancel(current.sfx.handler);
        mmUnloadEffect(current.id);
        break;

    default:
        break;
    }

}