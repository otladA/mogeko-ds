#pragma once

#include "graphics.h"

typedef enum{
    BG_FUNAMUSEA_LOGO,
    BG_MOGEKO_WARNING,
    BG_MOGEBED,
} BackgroundId;

Image *get_background(BackgroundId id);