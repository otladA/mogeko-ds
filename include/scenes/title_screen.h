/**
 * @file title_screen.h
 * @brief Title screen with menu navigation.
 */

#pragma once

#include <stdint.h>

/**
 * @brief A selectable menu item rendered as an OAM sprite.
 * 
 * Each item has two graphics variants (normal and selected) and
 * switches between them by swapping the palette index.
 * 
 */
typedef struct{
    uint16_t *gfx_normal;    ///< VRAM pointer for the unselected sprite tiles.
    uint16_t *gfx_selected;  ///< VRAM pointer for the selected/highlighted sprite tiles.
    int oam_id;              ///< OAM sprite ID (0-based index).
    int x, y;                ///< Screen position in pixels.
    int palette_idx;         // OAM palette index (highlight uses palette_idx - 2).
    int enabled;             // 0 = disabled (still rendered), 1 = active.
} MenuItem;

/**
 * @brief State for the title screen scene.
 * 
 * Contains two menu items: New Game (items[0]) and
 * Continue (items[1]).
 * 
 * The cursor index determines which item is visually highlighted.
 * 
 * @attention Only New Game (items[0]) triggers the finished flag.
 * Continue is currently disabled and non-functional.
 */
typedef struct{
    int timer;              ///< Frame counter (unused but reserved for future animations).
    int finished;           ///< 1 when the player has selected New Game.
    int cursor;             ///< Index of the currently highlighted menu item (0 or 1).
    MenuItem items[2];      ///< Menu items: item[0] = New game, item[1] = Continue.
} TitleState;

/**
 * @brief Initialize the title screen scene.
 * 
 * Loads the title background on the main engine, fades in over 3 seconds,
 * starts the main theme music (looped), and allocates 4 OAM sprites
 * (normal + selected variants for each menu item).
 * 
 * @return Pointer to the static TitleState.
 */
TitleState *title_init(void);

/**
 * @brief Run one frame of the title screen.
 * 
 * Handles cursos navigation (KEY_UP/KEY_DOWN) and selection (KEY_A).
 * Updates OAM sprites to reflect the highlighted item by swapping 
 * the sprite graphic and palette. Only New Game sets the finished flag.
 * 
 * @param state Pointer to the TitleState.
 */
void title_update(TitleState *state);

/**
 * @brief Check if the title screen has completed.
 * 
 * @param state Pointer to the TitleState.
 * @return 1 if New Game was selected, 0 otherwise.
 */
int title_is_finished(TitleState *state);

/**
 * @brief Clean up all title screen resources.
 * 
 * Frees the 4 OAM sprite allocations, clears the OAM, and stops
 * audio playback. Called by the scene manager before transitioning.
 * 
 * @param state Pointer to the TitleState.
 */
void title_cleanup(TitleState *state);