#include "backgrounds.h"

#include "mogebed.h"
#include "yonaka_dialogue.h"

Background registry[] = {
    [BG_MOGEBED] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = MAIN, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = mogebedPal, .palette_len = mogebedPalLen,
        .bitmap = {mogebedBitmap, mogebedBitmapLen},
    },
    
    [DIAL_YONAKA_IDLE] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = SUB, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = yonaka_dialoguePal, .palette_len = yonaka_dialoguePalLen, .palette_offset = 16,
        .bitmap = {yonaka_dialogueBitmap, yonaka_dialogueBitmapLen},
    }
};

Background *get_background(BackgroundId id){
    return &registry[id];
}