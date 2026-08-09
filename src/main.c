#include <nds.h>
#include <stdio.h>

#include <game.h>

int main(){
	GameContext ctx = {0};
	game_init(&ctx);
	
	while(pmMainLoop()) {
		game_update(&ctx);
		swiWaitForVBlank();
	}
    
    return 0;
}