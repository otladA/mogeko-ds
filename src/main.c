/**
 * @file main.c
 * @brief Application entry point.
 */

#include <nds.h>
#include <stdio.h>

#include <game.h>

/**
 * @brief Program entry point.
 * 
 * Initializes the game context, then enters the main loop.
 * Each interation processes one frame via game_update() and
 * waits for VBlank. Exits when pmMainLoop() returns false.
 * 
 * @return 0 on clean exit. 
 */
int main(){
	GameContext ctx = {0};		///< Zero-initialized game context.
	game_init(&ctx);
	
	while(pmMainLoop()) {
		game_update(&ctx);
		swiWaitForVBlank();
	}
    
    return 0;
}