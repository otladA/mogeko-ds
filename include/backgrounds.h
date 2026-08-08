#pragma once

#include "graphics.h"

typedef enum{
    BG_FUNAMUSEA_LOGO,
    BG_MOGEKO_WARNING,
    BG_MOGEBED,
    // Dialogue Sprites
    // Yes, I know using them as backgrounds doesnt really make sense
    // but it works
    DIAL_YONAKA_IDLE,
} BackgroundId;

Background *get_background(BackgroundId id);