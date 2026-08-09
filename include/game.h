#pragma once

#include <scene_manager.h>

typedef struct GameContext GameContext;

struct GameContext{
	SceneID current_scene;
	void* scene_state;
};

void game_update(GameContext *ctx);
void game_init(GameContext *ctx);