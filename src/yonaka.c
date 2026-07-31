#include <yonaka.h>

void initYonaka(Yonaka *sprite, u8* gfx){
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
	sprite->frame_gfx = (u8*)gfx;
}