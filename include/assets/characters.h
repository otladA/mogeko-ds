#pragma once

#include <graphics.h>

typedef enum{
    YONAKA,
    
} CharacterId;

typedef enum{
    // Yonaka
    YONAKA_IDLE,
} CharacterPortraitId;

Image *get_char_portrait(CharacterPortraitId id);