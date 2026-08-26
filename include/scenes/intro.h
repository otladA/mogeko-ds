/**
 * @file intro.h
 * @brief Opening intro scene displayed after the title screen.
 */

#pragma once

/**
 * @brief State for the intro scene.
 * 
 * Managed internally by intro_init(), intro_update(), and intro_cleanup().
 * 
 * The state field tracks the current phase of the intro sequence.
 * 
 * @attention The state field uses an internal IntroPhase enum — do not assign raw integers.
 * Use the phase transitions driven by intro_update().
 * 
 */
typedef struct{
    int state;
    int timer;
    int finished;
} IntroState;

/**
 * @brief Initialize the intro scene.
 * 
 * Resets state to INTRO_LOGO, loads the Funamusea logo background
 * on the main engine, and performs a 3-second fade-in.
 * 
 * @return Pointer to the static IntroState.
 */
IntroState *intro_init(void);

/**
 * @brief Run one frame of the intro scene.
 * 
 * Increments the frame counter, scans input, and progresses through the intro phases:
 * 
 * - INTRO_LOGO: Logo display (~120 frames), KEY_START to skip.
 * 
 * - INTRO_WARNING: Warning screen (~650 frames), KEY_START to skip.
 * 
 * - INTRO_STORY: Dialog sequence with Strange Mogeko (18 lines).
 * 
 * - INTRO_STORY_FADE_OUT: Fade out + second dialog (3 lines).
 * 
 * - INTRO_COMPLETE: Sets finished flag.
 * 
 * @attention KEY_START can be used to skip any timed phase.
 * @param state Pointer to the IntroState.
 */
void intro_update(IntroState *state);

/**
 * @brief Check if the intro sequence is complete.
 * 
 * @param state Pointer to the IntroState.
 * @return 1 if the intro has finished, 0 otherwise.
 */
int  intro_is_finished(IntroState *state);

/**
 * @brief Clean up all intro resources.
 * 
 * Stops audio playback and frees both dialog instances
 * (intro_dialog and intro_dialog2) if they exist.
 * 
 * @param state Pointer to the IntroState.
 */
void intro_cleanup(IntroState *state);