#pragma once

#include <yonaka_dialogue.h>
#include <nds.h>

typedef struct
{
	int x;
	int y;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Yonaka;

void initYonaka(Yonaka *sprite, u8* gfx);