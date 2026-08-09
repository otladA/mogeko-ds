#pragma once

typedef struct GameContext GameContext;

typedef enum{
	SCENE_INTRO,
    // Will add more as the game progresses
} SceneID;

void scene_change(GameContext *ctx, SceneID new_scene);