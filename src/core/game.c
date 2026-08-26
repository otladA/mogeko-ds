#include <nds.h>
#include <calico/nds/irq.h>

#include <audio.h>
#include <game.h>
#include <intro.h>
#include <title_screen.h>

static volatile int frame = 0;

void Vblank(){
	frame += 1;
}

void game_init(GameContext *ctx){
	irqSet(IRQ_VBLANK, Vblank);
	mmInitDefaultMem((mm_addr)soundbank_bin);
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);		// 128kb
	vramSetBankB(VRAM_B_MAIN_SPRITE);	// 128kb
	vramSetBankC(VRAM_C_SUB_BG);		// 128kb

	// SpriteMapping_1D_128 : consecutive tiles are in blocks of 128 bytes in VRAM
	oamInit(&oamMain, SpriteMapping_1D_128, false);

	ctx->current_scene = SCENE_TITLE_SCR;
	ctx->scene_state = title_init();
}

void game_update(GameContext *ctx){
	switch(ctx->current_scene){
		case SCENE_TITLE_SCR:
			TitleState *title = (TitleState*)ctx->scene_state;

			title_update(title);

			if (title_is_finished(title)){
				scene_change(ctx, SCENE_INTRO);
			}

			break;
		
		case SCENE_INTRO:
			IntroState *intro = (IntroState*)ctx->scene_state;
			intro_update(intro);

			if (intro_is_finished(intro)){
				intro_cleanup(intro);
			}
			
			break;

	}
}