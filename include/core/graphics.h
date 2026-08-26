/**
 * @file graphics.h
 * @brief Graphics loading and rendering utilities
 */

#pragma once

#include <nds.h>

/**
 * @brief Graphics rendering mode.
 * @warning Tile-based background mode not functional.
 */
typedef enum{
    GFX_MODE_TILE,      ///< Tile-based background mode (not yet implemented).
    GFX_MODE_BITMAP     ///< Direct bitmap mode via DMA copy
} GfxMode;

/**
 * @brief Target engine screen
 */
typedef enum{
    MAIN = 1,   ///< Main engine (top screen).
    SUB = 2,    ///< Sub engine (bottom screen).
    BOTH = 3    ///< Both engines.
} EngineMode;

/**
 * @brief Tile-based graphic data
 */
typedef struct{
    u16 *data;      ///< Pointer to tile data.
    int count;      ///< Number of tiles.
    int tilebase;   ///< VRAM tile base offset.
} Tile;

/**
 * @brief Bitmap graphic data.
 */
typedef struct{
    unsigned int *data; ///< Pointer to bitmap pixel data.
    u32 length;         ///< Length of bitmap data in bytes;
    int mapbase;        ///< VRAM map base offset.
} Bitmap;

/**
 * @brief Complete image asset with metadata
 */
typedef struct{
    GfxMode gfx_mode;              ///< Rendering mode.
    EngineMode engine_mode;        ///< Target Engine.
    short unsigned int *palette_data; ///< Palette color data.
    short unsigned int palette_len;   ///< Number of palette entries.
    BgType type;                   ///< NDS background type.
    BgSize size;                   ///< NDS background size.
    int id;                        ///< Background layer ID.
    int layer;                     ///< Display layer order.
    int palette_offset;            ///< Palette VRAM offset.

    union{
        Tile tile;      ///< Tile data (when gfx_mode is GFX_MODE_TILE).
        Bitmap bitmap;  ///< Bitmap data (when gfx_mode is GFX_MODE_BITMAP).
    };

} Image;

/**
 * @brief Load an image asset into VRAM.
 * 
 * Copies bitmap data and palette via DMA to the appropriate engine's 
 * VRAM, then calls bgUpdate().
 * Does nothing if @p img is NULL.
 * 
 * @param img Pointer to the Image to load (e.g. from get_background()).
 */
void img_load(Image *img);

/**
 * @brief Initialize and get the background layer ID.
 * 
 * Calls bgInit for MAIN or bgInitSub for SUB and stores
 * the returned ID in img->id. Returns 0 if @p img is NULL.
 * 
 * @param img Pointer to the Image to initialize.
 * @return The NDS background layer ID, or 0 on failure.
 */
int get_img_id(Image *img);

/**
 * @brief Fade in a screen from black.
 * 
 * Brightness ramps from -16 (black) to 0 (normal) in
 * 17 discreete steps, waiting ~16ms per VBlank between each.
 * 
 * Typical usage: img_fade_in(MAIN, 3000, 64).
 * 
 * @param screen        Target engine (MAIN, SUB, or BOTH).
 * @param duration_ms   Approximate duration in milliseconds.
 * @param fade_steps    Delay per brightness level (in VBlank counts).
 */
void img_fade_in(EngineMode screen, int duration_ms, int fade_steps);

/**
 * @brief Fade out a screen to black.
 * 
 * Ramps brightness from 0 (normal) to -16 (fully black) in
 * 17 discrete steps, waiting ~16ms per VBlank between each.
 * Typical usage img_fade_out(MAIN, 3000, 64).
 * 
 * @param screen        Target engine (MAIN, SUB, or BOTH).
 * @param duration_ms   Approximate duration in milliseconds.
 * @param fade_steps    Delay per brightness level (in VBlank counts).
 */
void img_fade_out(EngineMode screen, int duration_ms, int fade_steps);

/**
 * @brief Transition between two images with a fade effect.
 * 
 * Calls img_fade_out() (3000ms), loads the new image via img_load(),
 * then calls img_fade_in() (3000ms). Does nothing if @p new_img is NULL.
 * 
 * Typical usage: img_transition(MAIN, get_background(BG_MOGEKO_WARNING), 64).
 * 
 * @param screen        Target engine (MAIN, SUB, or BOTH).
 * @param new_img       New image to display (from get_background() or get_char_portrait()).
 * @param fade_steps    Delay per brightness level for each fade.
 */
void img_transition(EngineMode screen, Image *new_img, int fade_steps);