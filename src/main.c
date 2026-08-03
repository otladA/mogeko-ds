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

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

	int cg_spr = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(mogebedBitmap, bgGetGfxPtr(cg_spr), mogebedBitmapLen);
	dmaCopy(mogebedPal, BG_PALETTE, mogebedPalLen);

	int dialogue_spr = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(yonaka_dialogueBitmap, bgGetGfxPtr(dialogue_spr), yonaka_dialogueBitmapLen);
	dmaCopy(yonaka_dialoguePal, BG_PALETTE_SUB, yonaka_dialoguePalLen);

	while(pmMainLoop()) {
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		
		swiWaitForVBlank();
	}
    
    return 0;
}