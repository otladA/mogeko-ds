#include "graphics.h"

void img_load(Image *img){
    if (img == NULL){
        return;
    }

    switch (img->gfx_mode){
        case GFX_MODE_BITMAP:
            dmaCopy(img->bitmap.data, bgGetGfxPtr(get_img_id(img)), img->bitmap.length);

            if (img->engine_mode != MAIN){
                dmaCopy(img->palette_data, BG_PALETTE_SUB + img->palette_offset, img->palette_len);
            } else{
                dmaCopy(img->palette_data, BG_PALETTE + img->palette_offset, img->palette_len);
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

int get_img_id(Image *img){

    switch (img->engine_mode){
        case MAIN:
            img->id = bgInit(img->layer, img->type, img->size, 0, 0);
            return img->id;
            break;
        
        case SUB:
            img->id = bgInitSub(img->layer, img->type, img->size, 0, 0);
            return img->id;
            break;
        
        default:
            return 0;
            break;
    }
}

void img_fade_in(EngineMode screen, int duration_ms, int fade_steps){
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
void img_fade_out(EngineMode screen, int duration_ms, int fade_steps){
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

void img_transition(EngineMode screen, Image *new_img, int fade_steps){
    img_fade_out(screen, 3000, fade_steps);
    img_load(new_img);
    img_fade_in(screen, 3000, fade_steps);
}