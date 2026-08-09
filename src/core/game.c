#include <nds.h>
#include <calico/nds/irq.h>

#include <audio.h>
#include <game.h>
#include <intro.h>

static volatile int frame = 0;

void Vblank(){
	frame += 1;
}

void game_init(GameContext *ctx){
	irqSet(IRQ_VBLANK, Vblank);
	mmInitDefaultMem((mm_addr)soundbank_bin);
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);	// 128kb
	vramSetBankC(VRAM_C_SUB_BG);	// 128kb

	ctx->current_scene = SCENE_INTRO;
	ctx->scene_state = intro_init();
}

void game_update(GameContext *ctx){
    scanKeys();

	switch(ctx->current_scene){
		case SCENE_INTRO: {
			IntroState *intro = (IntroState*)ctx->scene_state;
			intro_update(intro);

		// TODO:
		//	if (intro_is_finished(intro))
		}
		break;
	}
}