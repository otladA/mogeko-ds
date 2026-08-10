#pragma once

#include <nds.h>

typedef enum{
    GFX_MODE_TILE,
    GFX_MODE_BITMAP
} GfxMode;

typedef enum{
    MAIN = 1,
    SUB = 2,
    BOTH = 3
} EngineMode;

typedef struct{
    u16 *data;
    int count;
} Tile;

typedef struct{
    unsigned int *data;
    u32 length;
} Bitmap;

typedef struct{
    GfxMode gfx_mode;
    EngineMode engine_mode;
    short unsigned int *palette_data;
    short unsigned int palette_len;
    BgType type;
    BgSize size;
    int id;
    int layer;
    int palette_offset;

    union{
        Tile tile;
        Bitmap bitmap;
    };

} Image;

void img_load(Image *img);
int get_img_id(Image *img);
void img_fade_in(EngineMode screen, int duration_ms, int fade_steps);
void img_fade_out(EngineMode screen, int duration_ms, int fade_steps);
void img_transition(EngineMode screen, Image *new_img, int fade_steps);