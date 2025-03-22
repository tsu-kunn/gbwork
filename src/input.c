#include <gb/gb.h>
#include <stdint.h>
#include "input.h"

uint8_t inputOld = 0;
uint8_t inputDir = 0;
uint8_t inputSeq = 0;
uint8_t inputTri = 0;

void UpdateInput(void)
{
    inputOld = inputDir;
    inputDir = joypad();
    inputSeq = inputDir & (inputSeq ^ inputDir);
    inputTri = inputDir & (inputDir ^ inputOld);
}
