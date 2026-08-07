#pragma once

#include "graphics.h"

typedef enum{
    BG_MOGEBED,
    DIAL_YONAKA_IDLE
} BackgroundId;

Background *get_background(BackgroundId id);