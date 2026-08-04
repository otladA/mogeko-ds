#include <nds.h>
#include <maxmod9.h>
#include <stdio.h>
#include <calico/nds/irq.h>
#include <yonaka_dialogue.h>
#include <mogebed.h>

#include "soundbank.h"
#include "soundbank_bin.h"
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

	// set IDs
	int cg_spr = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);				// Main
	int dialogue_art_id = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);	// Sub
	int text_id = bgInitSub(0, BgType_Text4bpp, BgSize_T_256x256, 0, 0);		// Sub

	// Enable console for dialogue
	PrintConsole text;
	consoleInit(&text, 0, BgType_Text4bpp, BgSize_T_256x256, 24, 4, false, true);

	windowEnableSub(WINDOW_0);
	windowSetBoundsSub(WINDOW_0, 85, 120, 248, 176);
	
	bgWindowEnable(text_id, WINDOW_0);
	bgWindowDisable(text_id, WINDOW_OUT);
	bgWindowEnable(dialogue_art_id, WINDOW_OUT);
	bgWindowDisable(dialogue_art_id, WINDOW_0);
	
	consoleSelect(&text);
	iprintf("\x1b[16;11HTEMPLATE TEXT");

	// Write background art for Main + Sub to memory
	dmaCopy(mogebedBitmap, bgGetGfxPtr(cg_spr), mogebedBitmapLen);
	dmaCopy(mogebedPal, BG_PALETTE, mogebedPalLen);

	dmaCopy(yonaka_dialogueBitmap, bgGetGfxPtr(dialogue_art_id), yonaka_dialogueBitmapLen);
	// BG_PALLETE_SUB + 16 --> had to make an offset for 16 bytes for dialogue text
	// Managed to create that offset from .grit file --> gA16
	dmaCopy(yonaka_dialoguePal, BG_PALETTE_SUB + 16, yonaka_dialoguePalLen);

	while(pmMainLoop()) {
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		
		swiWaitForVBlank();
	}
    
    return 0;
}