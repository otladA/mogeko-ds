#include <nds.h>
#include <stdio.h>
#include <calico/nds/irq.h>
#include <yonaka_dialogue.h>

#include "console_util.h"

static volatile int frame = 0;

void Vblank(){
	frame += 1;
}

int main(){
    irqSet(IRQ_VBLANK, Vblank);

	videoSetModeSub(MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE);
	vramSetBankH(VRAM_H_SUB_BG);

	int art = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(yonaka_dialogueBitmap, bgGetGfxPtr(art), yonaka_dialogueBitmapLen);
	dmaCopy(yonaka_dialoguePal, BG_PALETTE_SUB, yonaka_dialoguePalLen);

	while(pmMainLoop()) {
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		
		swiWaitForVBlank();
	}
    
    return 0;
}