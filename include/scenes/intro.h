#pragma once

typedef struct{
    int state;
    int timer;
    int finished;
} IntroState;

IntroState *intro_init(void);
void intro_update(IntroState *state);
int  intro_is_finished(IntroState *state);
void intro_cleanup(IntroState *state);