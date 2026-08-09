#include <scene_manager.h>
#include <game.h>

#include <intro.h>

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