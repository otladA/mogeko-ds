#include "characters.h"

#include "yonaka_dialogue_idle.h"

Image char_registry[] = {
    [YONAKA_IDLE] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = SUB, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = yonaka_dialogue_idlePal, .palette_len = yonaka_dialogue_idlePalLen, .palette_offset = 16,
        .bitmap = {yonaka_dialogue_idleBitmap, yonaka_dialogue_idleBitmapLen, 0}
    },
};

Image *get_char_portrait(CharacterPortraitId id){
    return &char_registry[id];
}