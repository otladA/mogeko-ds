#include "backgrounds.h"

#include "mogebed.h"
#include "mogeko_warning.h"
#include "funamusea_logo.h"

Image bg_registry[] = {
    [BG_FUNAMUSEA_LOGO] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = MAIN, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = funamusea_logoPal, .palette_len = funamusea_logoPalLen,
        .bitmap = {funamusea_logoBitmap, funamusea_logoBitmapLen, 0},
    },

    [BG_MOGEKO_WARNING] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = MAIN, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = mogeko_warningPal, .palette_len = mogeko_warningPalLen,
        .bitmap = {mogeko_warningBitmap, mogeko_warningBitmapLen, 0},
    },
    
    [BG_MOGEBED] = {
        .gfx_mode = GFX_MODE_BITMAP, .engine_mode = MAIN, .layer = 2,
        .type = BgType_Bmp8, .size = BgSize_B8_256x256,
        .palette_data = mogebedPal, .palette_len = mogebedPalLen,
        .bitmap = {mogebedBitmap, mogebedBitmapLen, 0},
    },
};

Image *get_background(BackgroundId id){
    return &bg_registry[id];
}