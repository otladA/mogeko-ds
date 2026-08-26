#pragma once

#include <stdint.h>

typedef struct{
    uint16_t *gfx_normal;    // VRAM pointer of normal sprite
    uint16_t *gfx_selected;  // VRAM pointer of selected sprite
    int oam_id;         
    int x, y;
    int palette_idx;         // index for OAM palette
    int enabled;             // 0 = false; 1 = true;
} MenuItem;

typedef struct{
    int timer;
    int finished;
    int cursor;
    MenuItem items[2];       // New Game, Continue.
} TitleState;

TitleState *title_init(void);
void title_update(TitleState *state);
int title_is_finished(TitleState *state);
void title_cleanup(TitleState *state);