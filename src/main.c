#include <nds.h>
#include <stdio.h>
#include <calico/nds/irq.h>

#include "backgrounds.h"
#include "audio.h"
#include "console_util.h"

static volatile int frame = 0;

void Vblank(){
	frame += 1;
}

int main(){
    irqSet(IRQ_VBLANK, Vblank);

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG);	// 128kb
	vramSetBankC(VRAM_C_SUB_BG);	// 128kb
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	// -------------

	play_song(MOD_MAIN_THEME, true);

	Background *mogebed = get_background(BG_MOGEBED);
	Background *yonaka_idle = get_background(DIAL_YONAKA_IDLE);

	int text_id = bgInitSub(0, BgType_Text4bpp, BgSize_T_256x256, 0, 0); // Sub

	// // Enable console for dialogue
	PrintConsole text;
	consoleInit(&text, 0, BgType_Text4bpp, BgSize_T_256x256, 24, 4, false, true);

	windowEnableSub(WINDOW_0);
	windowSetBoundsSub(WINDOW_0, 85, 120, 248, 176);
	
	bgWindowEnable(text_id, WINDOW_0);
	bgWindowDisable(text_id, WINDOW_OUT);
	bgWindowEnable(get_bg_id(yonaka_idle), WINDOW_OUT);
	bgWindowDisable(get_bg_id(yonaka_idle), WINDOW_0);
	
	consoleSelect(&text);
	iprintf("\x1b[16;11HTEMPLATE TEXT");

	// Write background art for Main + Sub to memory

	bg_load(mogebed);
	bg_load(yonaka_idle);

	while(pmMainLoop()) {
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		
		swiWaitForVBlank();
	}
    
    return 0;
}