#include "graphics.h"

void bg_load(Background *bg){
    if (bg == NULL){
        return;
    }

    switch (bg->gfx_mode){
        case GFX_MODE_BITMAP:
            dmaCopy(bg->bitmap.data, bgGetGfxPtr(get_bg_id(bg)), bg->bitmap.length);

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

int get_bg_id(Background *bg){

    switch (bg->engine_mode){
        case MAIN:
            bg->id = bgInit(bg->layer, bg->type, bg->size, 0, 0);
            return bg->id;
            break;
        
        case SUB:
            bg->id = bgInitSub(bg->layer, bg->type, bg->size, 0, 0);
            return bg->id;
            break;
        
        default:
            return 0;
            break;
    }
}