/**
 * @file audio.h
 * @brief Audio playback system for music and sound effects.
 */

#pragma once

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#define MAX_VOLUME 255

/**
 * @brief Stereo panning position for audio output.
 */
typedef enum{
    LEFT = 0,       ///< Full left channel.
    CENTER = 127,   ///< Balanced stereo (default).
    RIGHT = 255     ///< Full right channel.
} Panning;

/**
 * @brief Type of currently playing audio.
 */
typedef enum{
    SFX,    ///< Short sound effect (.WAV).
    SONG    ///< Music track (.MOD).
} AudioType;

/**
 * @brief Sound effect state including maxmod handler.
 */
typedef struct{
    mm_sound_effect sound;  ///< Maxmod sound effect discriptor.
    mm_sfxhand handler;     ///< Handle for controlling playback (cancel, reuse).
} Sfx;

/**
 * @brief Music track state.
 */
typedef struct{
    bool loop;  ///< Whether the song loops indefinitely.
} Song;

/**
 * @brief Currently playing audio descriptor.
 * 
 * Tracks the active audio so that play_sfx() can reuse handlers
 * and audio_cleanup() knows what to stop.
 * 
 * @attention Only one audio source (song or sfx) is tracked at a time.
 * Calling play_song() while an SFX is playing will overwrite the state.
 */
typedef struct{
    AudioType type;     ///< Type of currently playing audio.
    mm_word id;         ///< Maxmod ID of the loaded audio.

    union{
        Sfx sfx;        ///< SFX state (valid when type == SFX).
        Song song;      ///< Song state (valid when type == SONG).
    };

} Audio;

/**
 * @brief Loads and plays a .MOD Music Track.
 * 
 * Stops any currently playing music or SFX via mmStop() before 
 * loading and starting the new track to prevent overlapping playback.
 * 
 * @param song_id Maxmod module ID from the soundbank (e.g. MOD_MAIN_THEME)
 * @param loop    If true, loops indefinitely; if false, plays once.
 */
void play_song(mm_word song_id, bool loop);

/**
 * @brief Plays a short .WAV sound effect.
 * 
 * Loads the effect on first use. Reuses the handler for the same effect to
 * avoid redundant loads. Only the most recent SFX is tracked — calling play_sfx()
 * overwrites the previous one.
 * 
 * @param sfx_id    Maxmod effect ID from the soundbank (e.g. SFX_TEXT_BLEEP)
 * 
 * @param volume    Playback volume. Range: 0 (silent) to 255 (max).
 * @param panning   Stereo panning. Use LEFT, CENTER, or RIGHT.
 */
void play_sfx(mm_word sfx_id, int volume, Panning panning);

/**
 * @brief Stop and unload the currently playing audio.
 * 
 * Safely stops playback and unload resources depending on the
 * current audio type:
 * 
 * - SONG: calls mmStop() + mmUnload().
 * 
 * - SFX: calls mmEffectCancel() + mmUnloadEffect().
 * 
 * Safe to call even if no audio is playing.
 * 
 * @attention Must be called before switching scenes to prevent
 * stale audio handles from persisting.
 * 
 */
void audio_cleanup();