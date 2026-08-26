/**
 * @file dialog.h
 * @brief Typewriter-style dialog system with character portraits.
 */

#pragma once

#include <nds.h>
#include "characters.h"
#include <maxmod9.h>

/** @brief Maximum number of dialog instances that can exist */
#define MAX_DIALOGS 64

/** @brief Maximum lines a single Dialog can hold. */
#define MAX_LINES_PER_DIALOG 20

/** @brief Maximum length of a single dialog line string */
#define MAX_DIALOGUE_LENGTH 256

/** @brief Characters per line before automatic word wrap */
#define MAX_CHARS_PER_LINE 19

/** @brief Maximum visible text lines in the dialog box */
#define MAX_TEXT_LINES 3

/** @brief Default frames between each typed character (2 = ~32ms). */
#define TYPING_SPEED 2

/** @brief Play a typing bleep every N characters */
#define TYPING_BLEEP_INTERVAL 3

/**
 * @brief A single line of dialog text.
 * 
 */
typedef struct{
    const char* speaker;        ///< Speaker name displayed above the text.
    const char* text;           ///< Dialog text content (supports '\\n').
    CharacterId speaker_id;     ///< Character ID for the portrait to display.
} DialogLine;

/**
 * @brief Complete dialog state including typing animation.
 * 
 * Allocated via dialog_create(), freed via dialog_cleanup().
 * 
 * Lifecycle: create -> add lines -> open -> update loop -> cleanup.
 * 
 * @warning Always call dialog_cleanup() when done to avoid memory leaks.
 */
typedef struct{
    PrintConsole console;                    ///< NDS console for text rendering on sub engine.
    DialogLine lines[MAX_LINES_PER_DIALOG];  ///< Array of dialog lines.
    int line_count;                          ///< Total number of lines added.
    int current_line;                        ///< Index of the line currently being displayed.
    int finished;                            ///< 1 when all lines have been shown.
    int is_open;                             ///< 1 when the dialog box is visible.

    int typing_progress;                     ///< Characters typed so far in the current line.
    int typing_timer;                        ///< Frame counter for typing speed timing.
    int text_fully_displayed;                ///< 1 when the current line is fully typed out.
    int typing_speed;                        ///< Frames per character (lower = faster).
    mm_word typing_sound_id;                 ///< Sound effect ID played while typing.
} Dialog;

/**
 * @brief Allocate and initialize a new Dialog.
 * 
 * @attention Must be freed with dialog_cleanup() when no longer needed.
 * 
 * @param line_count Number of lines this dialog will contain (max 20). 
 * @return Pointer to the newly allocated Dialog.
 */
Dialog *dialog_create(int line_count);

/**
 * @brief Add a line of dialog text.
 * 
 * Lines are added sequentially. Does nothing if MAX_LINES_PER_DIALOG is reached.
 * 
 * Must be called before dialog_open().
 * 
 * @param dialog        Pointer to the Dialog.
 * @param speaker       Speaker name string (displayed at top).
 * @param text          Dialog text (supports '\\n' for line breaks).
 * @param speaker_id    Character ID used to select the portrait.
 */
void dialog_add_line(Dialog *dialog, const char* speaker, const char* text, CharacterId speaker_id);

/**
 * @brief Open and display the dialog box on the sub engine.
 * 
 * Initializes a PrintConsole on layer 4, sets up a sub engine windowing
 * (bounds 85, 120, 248, 176), and loads the character portrait.
 * 
 * Resets to line 0. Does nothing if already open.
 * 
 * @attention Must be called after dialog_add_line() and before
 * dialog_update().
 * 
 * @param dialog    Pointer to the Dialog.
 * @param char_id   Portrait ID for the character image (e.g. STRANGE_MOGE_IDLE)
 */
void dialog_open(Dialog *dialog, CharacterPortraitId char_id);

/**
 * @brief Update the dialog one frame (typing animation + input).
 * 
 * Handles the typewriter effect by incrementing typing_progress each
 * typing_speed frames. Plays typing bleep at every TYPING_BLEEP_INTERVAL
 * characters.
 * 
 * Input behavior:
 * 
 * - KEY_A while typing: instantly completes the current line.
 * 
 * - KEY_A while fully displayed: advances to the next line.
 * 
 * - When all lines are shown, sets finished = 1. 
 * 
 * @param dialog Pointer to the Dialog.
 */
void dialog_update(Dialog *dialog);

/**
 * @brief Render the current dialog line to the console.
 * 
 * Prints the speaker name at row 1, then the partially or fully typed
 * text below. Text wraps automatically at MAX_CHARS_PER_LINE (19)
 * and is clipped at MAX_TEXT_LINES (3) visible rows.
 * 
 * @attention Usually called automatically by dialog_update(); call manually only
 * for the initial render after dialog_open().
 * 
 * @param dialog Pointer to the dialog
 */
void dialog_render(Dialog *dialog);

/**
 * @brief Check if all dialog lines have been displayed.
 * 
 * @param dialog Pointer to the Dialog.
 * @return 1 if finished, 0 otherwise.
 */
int dialog_is_finished(Dialog *dialog);

/**
 * @brief Close the dialog box without freeing memory.
 * 
 * Disables the sub engine window and clears the console.
 * The Dialog can be reopened with dialog_open() if needed.
 * 
 * @param dialog Pointer to the Dialog.
 */
void dialog_close(Dialog *dialog);

/**
 * @brief Close and free all dialog memory.
 * 
 * Calls dialog_close() internally, then frees the Dialog pointer.
 * 
 * @warning The Dialog pointer is invalid after this call.
 * 
 * @param dialog Pointer to the Dialog to destroy.
 */
void dialog_cleanup(Dialog *dialog);

/**
 * @brief Set the typing speed for a dialog.
 * 
 * @param dialog Pointer to the dialog
 * @param speed Frames per character (2 = default, lower = faster).
 */
void dialog_set_typing_speed(Dialog *dialog, int speed);

/**
 * @brief Set the sound effect played while typing.
 * 
 * @param dialog    Pointer to the Dialog.
 * @param sound_id  maxmod SFX ID (default is SFX_TEXT_BLEEP).
 */
void dialog_set_typing_sound(Dialog *dialog, int sound_id);