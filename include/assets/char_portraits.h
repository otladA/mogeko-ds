#pragma once

#include <graphics.h>

typedef enum{
    // Yonaka
    YONAKA_IDLE,
} CharacterId;

Image *get_char_portrait(CharacterId id);