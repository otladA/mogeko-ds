/**
 * @file game.h
 * @brief Core game loop and context management.
 */

#pragma once

#include <scene_manager.h>

typedef struct GameContext GameContext;

/**
 * @brief Central game context holding the active scene and its state.
 * 
 * Managed by game_init() and game_update(). The scene_state pointer
 * is cast to the appropriate scene-specific type (e.g. TileState*, IntroState*)
 * based on the current_scene value.
 * 
 * @warning scene_state is a void* — always cast it to the correct
 * type matching current_scene before use.
 * 
 */
struct GameContext{
	SceneID current_scene;		///< Active scene identifier.
	void* scene_state;			///< Opaque pointer to the current scene's state.
};

/**
 * @brief Initialize the game hardware and start the first scene.
 * 
 * Perform full hardware setup:
 * 
 * - Registers VBlank interrupt handler for frame counting.
 * 
 * - Initializes audio system with default soundbank.
 * 
 * - Configures both video engines to MODE_5_2D.
 * 
 * - Maps VRAM banks: A -> main BG, B -> main sprites, C -> sub BG.
 * 
 * - Initializes OAM with 1D 128-byte sprite mapping.
 * 
 * - Starts the game at SCENE_TITLE_SCR via title_init().
 * 
 * @attention Call this once before entering the main loop.
 * @param ctx Pointer to the GameContext to initialize.
 */
void game_init(GameContext *ctx);

/**
 * @brief Run one frame of the active scene.
 * 
 * Dispatches to the current scene's update function and checks for scene completion:
 * 
 * - SCENE_TITLE_SCR: Transitions to SCENE_INTRO via scene_change()
 *   when title screen is finished.
 * 
 * - SCENE_INTRO: Calls intro_cleanup() when intro is finished.
 *
 * @param ctx Pointer to the GameContext with a valid current_scene.
 */
void game_update(GameContext *ctx);

