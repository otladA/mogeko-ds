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

    bgUpdate();
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

void bg_fade_in(EngineMode screen, int duration_ms, int fade_steps){
    int frames = (duration_ms + 8) / 16;
    int fade_frames = fade_steps;
    int delay_per_level = frames / fade_frames;

    for (int brightness = -16; brightness <= 0; brightness++){
        setBrightness(screen, brightness);

        for (int j = 0; j < delay_per_level; j++){
            swiWaitForVBlank();
        }
    }

}
void bg_fade_out(EngineMode screen, int duration_ms, int fade_steps){
    int frames = (duration_ms + 8) / 16;
    int fade_frames = fade_steps;
    int delay_per_level = frames / fade_frames;

    for (int brightness = 0; brightness >= -16; brightness--){
        setBrightness(screen, brightness);

        for (int j = 0; j < delay_per_level; j++){
            swiWaitForVBlank();
        }
    }
}

void bg_transition(EngineMode screen, Background *new_bg, int fade_steps){
    bg_fade_out(screen, 3000, fade_steps);
    bg_load(new_bg);
    bg_fade_in(screen, 3000, fade_steps);
}