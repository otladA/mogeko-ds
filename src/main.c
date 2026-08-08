#include <nds.h>
#include <stdio.h>
#include <calico/nds/irq.h>

#include "audio.h"
#include "intro.h"
#include "graphics.h"

static volatile int frame = 0;

void Vblank(){
	frame += 1;
}

typedef enum{
	SCENE_INTRO,
} SceneID;

typedef struct{
	SceneID current_scene;
	void* scene_state;
} GameContext;

void init(GameContext *ctx){
	irqSet(IRQ_VBLANK, Vblank);
	mmInitDefaultMem((mm_addr)soundbank_bin);
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);	// 128kb
	vramSetBankC(VRAM_C_SUB_BG);	// 128kb

	ctx->current_scene = SCENE_INTRO;
	ctx->scene_state = intro_init();
}

void scene_change(GameContext *ctx, SceneID new_scene){
	switch (ctx->current_scene){
		case SCENE_INTRO:
			intro_cleanup((IntroState*)ctx->scene_state);
			break;

		default:
			break;
	}

	ctx->current_scene = new_scene;
	switch (new_scene){
		case SCENE_INTRO:
			ctx->scene_state = intro_init();
			break;
		
		default:
			break;
	}
}

void main_update(GameContext *ctx){
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

int main(){
	GameContext ctx = {0};
	init(&ctx);
	
	while(pmMainLoop()) {
		main_update(&ctx);
		swiWaitForVBlank();
	}
    
    return 0;
}