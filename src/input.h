#pragma once

#include <stdint.h>

extern uint8_t inputDir;
extern uint8_t inputSeq;
extern uint8_t inputTri;

// キー入力の更新
void UpdateInput(void);

// 即値
inline uint8_t GetDirect(void)
{
    return inputDir;
}

// トリガー値
inline uint8_t GetTrigger(void)
{
    return inputTri; 
}

// 連続的なトリガー値
inline uint8_t GetSequence(void)
{
    return inputSeq;
}

