/**
 * @file backgrounds.h
 * @brief Background image asset registry.
 */

#pragma once

#include "graphics.h"

/**
 * @brief Identifier for all background images in the game.
 */
typedef enum{
    BG_FUNAMUSEA_LOGO,
    BG_TITLE_SCR,
    BG_MOGEKO_WARNING,
    BG_MOGEBED,
} BackgroundId;

/**
 * @brief Get a pointer to a registred background image.
 * 
 * Returns a pointer to the static Image descriptor for the given
 * background. All backgrounds are 256x256 8-bit bitmaps on the 
 * main engine at layer 2.
 * 
 * @warning Currently no bounds checking — passing an invalid BackgroundId
 * will access out-of-bounds memory. 
 * 
 * @param id Background identifier (e.g. BG_TITLE_SCR).
 * @return Pointer to the Image descriptor (do not free).
 */
Image *get_background(BackgroundId id);