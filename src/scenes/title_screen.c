#include "title_screen.h"

#include "graphics.h"
#include "backgrounds.h"
#include "audio.h"

#include "titlescr_newgame.h"
#include "titlescr_newgame_selected.h"
#include "titlescr_continue.h"
#include "titlescr_continue_selected.h"

static TitleState title_state;

TitleState *title_init(void){
    title_state = (TitleState){0};
    title_state.timer = 0;
    title_state.finished = 0;
    title_state.cursor = 0;

    img_load(get_background(BG_TITLE_SCR));
    img_fade(MAIN, DEFAULT_FADE_DURATION_MS, DEFAULT_FADE_STEPS, IMG_FADE_IN);
    play_song(MOD_MAIN_THEME, true);

    uint16_t *ng_gfx = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);
    uint16_t *ng_selected_gfx = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);
    uint16_t *continue_gfx = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);
    uint16_t *continue_selected_gfx = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);

    dmaCopy(titlescr_newgameTiles, ng_gfx, titlescr_newgameTilesLen);
    dmaCopy(titlescr_newgame_selectedTiles, ng_selected_gfx, titlescr_newgame_selectedTilesLen);
    dmaCopy(titlescr_continueTiles, continue_gfx, titlescr_continueTilesLen);
    dmaCopy(titlescr_continue_selectedTiles, continue_selected_gfx, titlescr_continue_selectedTilesLen);

    dmaCopy(titlescr_newgame_selectedPal, SPRITE_PALETTE + 0 * 32, titlescr_newgame_selectedPalLen);    
    dmaCopy(titlescr_newgamePal, SPRITE_PALETTE + 1 * 32, titlescr_newgamePalLen);
    
    dmaCopy(titlescr_continuePal, SPRITE_PALETTE + 2 * 32, titlescr_continuePalLen);
    dmaCopy(titlescr_continue_selectedPal, SPRITE_PALETTE + 3 * 32, titlescr_continue_selectedPalLen);
    
    

    title_state.items[0] = (MenuItem){
        .gfx_normal = ng_gfx, .gfx_selected = ng_selected_gfx,
        .oam_id = 0, .x = 160, .y = 120, .palette_idx = 2, .enabled = true
    };

    title_state.items[1] = (MenuItem){
        .gfx_normal = continue_gfx, .gfx_selected = continue_selected_gfx,
        .oam_id = 1, .x = 160, .y = 140, .palette_idx = 2, .enabled = false
    };

    MenuItem newgame = title_state.items[0];
    MenuItem continue_btn = title_state.items[1];

    oamSet(&oamMain, newgame.oam_id, newgame.x, newgame.y, 0, 2, SpriteSize_64x32, SpriteColorFormat_16Color,
            ng_gfx, -1, false, false, false, false, false);

    oamSet(&oamMain, continue_btn.oam_id, continue_btn.x, continue_btn.y, 0, 2, SpriteSize_64x32, SpriteColorFormat_16Color,
            continue_gfx, -1, false, false, false, false, false);

    oamUpdate(&oamMain);

    return &title_state;
}

void title_update(TitleState *state){
    scanKeys();

    int down = keysDown();
    int old_cursor = state->cursor;

    if ((down &KEY_DOWN) && state->cursor < 1) state->cursor++;
    if ((down &KEY_UP) && state->cursor > 0) state->cursor--;
    
    if (state->cursor != old_cursor){
        MenuItem *prev = &state->items[old_cursor];
        MenuItem *curr = &state->items[state->cursor];

        oamSet(&oamMain, prev->oam_id, prev->x, prev->y, 0,
                prev->palette_idx, SpriteSize_64x32, SpriteColorFormat_16Color,
                prev->gfx_normal, -1, false, false, false, false, false);

        oamSet(&oamMain, curr->oam_id, curr->x, curr->y, 0,
                curr->palette_idx - 2, SpriteSize_64x32, SpriteColorFormat_16Color,
                curr->gfx_selected, -1, false, false, false, false, false);
    }

    if (down &KEY_A){
        if (state->cursor == 0){
            state->finished = 1;
        }
    }

    oamUpdate(&oamMain);
}

int title_is_finished(TitleState *state){
    return state->finished;
}

void title_cleanup(TitleState *state){
    oamFreeGfx(&oamMain, state->items[0].gfx_normal);
    oamFreeGfx(&oamMain, state->items[0].gfx_selected);
    oamFreeGfx(&oamMain, state->items[1].gfx_normal);
    oamFreeGfx(&oamMain, state->items[1].gfx_selected);
    
    oamClear(&oamMain, 0, 128);
    oamUpdate(&oamMain);

    audio_cleanup();
    
}