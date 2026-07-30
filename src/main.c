#include <nds.h>
#include <stdio.h>

#include "console_util.h"
#include <calico/nds/irq.h>

static volatile int frame = 0;

static void Vblank(){
    frame += 1;
}

int main(){

    touchPosition touchXY;
    irqSet(IRQ_VBLANK, Vblank);

    consoleDemoInit();

    char* tmp_str = "Olha so, voce descobriu um segredo gigatonico";

	iprintf("      Vambora catatau\n");
	iprintf("     \x1b[32mwww.devkitpro.org\n");
	iprintf("   \x1b[36;1mwww.drunkencoders.com\x1b[39m");

	while(pmMainLoop()) {
		swiWaitForVBlank();
		scanKeys();

		int keys = keysDown();
		if (keys & KEY_START) break;
        if (keys & KEY_SELECT){ iprintf("\x1b[10;0H%s", tmp_str); }
        if (keys & KEY_UP){ clearPrint(&tmp_str, 10);}

		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;column
        iprintf("\x1b[20;0HFrame = %d",frame);
		iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
		iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);

	}
    
    return 0;
}