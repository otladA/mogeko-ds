#include <nds.h>
#include <stdio.h>

void clearLine(int line){
    iprintf("\x1b[%d;0H", line);
    iprintf("\x1b[K");
}

void clearPrint(char** string, int line){
    if (strlen(*string) > consoleGetDefault()->consoleWidth){
        clearLine(line);
        clearLine(line + 1);
    }

    clearLine(line);
}