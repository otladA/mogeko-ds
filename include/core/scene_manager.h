/**
 * @file scene_manager.h
 * @brief Scene management system for game state transitions.
 * 
 */

#pragma once

typedef struct GameContext GameContext;

/**
 * @brief Identifier for each game scene.
 */
typedef enum{
    SCENE_TITLE_SCR,    ///< Title Screen with menu.
	SCENE_INTRO,        ///< Opening intro sequence.
    // Will add more as the game progresses
} SceneID;

/**
 * @brief Transition from the current scene to a new one.
 * 
 * Cleans up active scene, updates the current Scene ID, and initializes the new scene.
 * 
 * @param ctx           Pointer the game context.
 * @param new_scene     Scene to transition to.
 */
void scene_change(GameContext *ctx, SceneID new_scene);