#include "graphics.h"

void bg_load(int screen, int bg_layer, Background *bg){
    if (bg == NULL){
        return;
    }

    // Get ID
    if (bg->engine_mode != MAIN){
        bg->id = bgInitSub(bg_layer, bg->type, bg->size, 0, 0);
    } else{
        bg->id = bgInit(bg_layer, bg->type, bg->size, 0, 0);
    }

    switch (bg->gfx_mode){
        case GFX_MODE_BITMAP:
            dmaCopy(bg->bitmap.data, bgGetGfxPtr(bg->id), bg->bitmap.length);

            if (bg->engine_mode != MAIN){
                dmaCopy(bg->palette_data, BG_PALETTE_SUB + bg->palette_offset, bg->palette_len);
            } else{
                dmaCopy(bg->palette_data, BG_PALETTE + bg->palette_offset, bg->palette_len);
            }

            break;

        case GFX_MODE_TILE:
            // TODO
            break;

        default:
            break;
    }


}