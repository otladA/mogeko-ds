/**
 * @file characters.h
 * @brief Character portrait asset registry for dialog display.
 */

#pragma once

#include <graphics.h>

/**
 * @brief Base character indentifiers.
 * 
 * These values serve as the starting index for each character's
 * portrait range in CharacterPortraitId. For example, STRANGE_MOGEKO = 37
 * means all Strange Mogeko portraits start at index 37.
 */
typedef enum{
    YONAKA = 0,             ///< Yonaka (protagonist), portraits start at index 0.
    STRANGE_MOGEKO = 37,    ///< Strange Mogeko, portraits start at index 37.
} CharacterId;

/**
 * @brief Identifiers for individual character portrait images.
 * 
 * Each character has multiple portraits variants (idle, sad, angry, etc.).
 * Portrait indices are sequential within character's range.
 * 
 */
typedef enum{
    // Yonaka
    YONAKA_IDLE = 0,            ///< Yonaka neutral expression

    // Strange Mogeko
    STRANGE_MOGE_IDLE = 37,     ///< Strange Mogeko neutral expression.
    STRANGE_MOGE_THOUGHTFUL,    ///< Strange Mogeko thoughtful/pensive expression.
} CharacterPortraitId;

/**
 * @brief Get a pointer to a registered character portrait image.
 * 
 * Returns a pointer to the static Image descriptor for the given
 * portrait. All portraits are 256x256 8-bit bitmaps on the SUB
 * engine at layer 2.
 * 
 * @warning Currently no bounds checking — passing an invalid CharacterPortraitId
 * will access out-of-bounds memory.
 * 
 * @param id Portrait identifier (e.g. STRANGE_MOGE_IDLE).
 * @return Pointer to the Image descriptor (do not free).
 */
Image *get_char_portrait(CharacterPortraitId id);