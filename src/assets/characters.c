#include "characters.h"

#include "yonaka_dialogue_idle.h"
#include "strange_moge_idle.h"
#include "strange_moge_thoughtful.h"

Image char_registry[] = {
    // Yonaka
    [YONAKA_IDLE] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = SUB, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = yonaka_dialogue_idlePal, .palette_len = yonaka_dialogue_idlePalLen, .palette_offset = 16,
        .bitmap = {yonaka_dialogue_idleBitmap, yonaka_dialogue_idleBitmapLen, 0}
    },

    // Strange Mogeko
    [STRANGE_MOGE_IDLE] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = SUB, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = strange_moge_idlePal, .palette_len = strange_moge_idlePalLen, .palette_offset = 0,
        .bitmap = {strange_moge_idleBitmap, strange_moge_idleBitmapLen, 0}
    },

    [STRANGE_MOGE_THOUGHTFUL] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = SUB, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = strange_moge_thoughtfulPal, .palette_len = strange_moge_thoughtfulPalLen, .palette_offset = 0,
        .bitmap = {strange_moge_thoughtfulBitmap, strange_moge_thoughtfulBitmapLen, 0}
    },
};

Image *get_char_portrait(CharacterPortraitId id){
    return &char_registry[id];
}