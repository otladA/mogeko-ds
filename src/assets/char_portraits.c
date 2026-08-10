#include <char_portraits.h>

#include <yonaka_dialogue.h>

Image char_registry[] = {
    [YONAKA_IDLE] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = SUB, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = yonaka_dialoguePal, .palette_len = yonaka_dialoguePalLen, .palette_offset = 16,
        .bitmap = {yonaka_dialogueBitmap, yonaka_dialogueBitmapLen},
    },
};

Image *get_char_portrait(CharacterId id){
    return &char_registry[id];
}