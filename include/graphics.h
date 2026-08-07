#pragma once

#include <nds.h>

typedef enum{
    GFX_MODE_TILE,
    GFX_MODE_BITMAP
} GfxMode;

typedef enum{
    MAIN,
    SUB
} EngineMode;

typedef struct{
    u16 *data;
    int count;
} Tile;

typedef struct{
    u32 *data;
    u32 length;
} Bitmap;

typedef struct{
    GfxMode gfx_mode;
    EngineMode engine_mode;
    u32 *palette_data;
    u32 palette_len;
    BgType type;
    BgSize size;
    int id;
    int palette_offset;

    union{
        Tile tile;
        Bitmap bitmap;
    };

} Background;

void bg_load(int screen, int bg_layer, Background *bg);
// void bg_fade_out();
// void bg_fade_in();
// void bg_transition();