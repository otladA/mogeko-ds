#pragma once

#include <graphics.h>

typedef enum{
    YONAKA = 0,
    STRANGE_MOGEKO = 37,
} CharacterId;

typedef enum{
    // Yonaka
    YONAKA_IDLE = 0,

    // Strange Mogeko
    STRANGE_MOGE_IDLE = 37,
    STRANGE_MOGE_THOUGHTFUL,
} CharacterPortraitId;

Image *get_char_portrait(CharacterPortraitId id);