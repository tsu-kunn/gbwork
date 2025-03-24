#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdint.h>
#include <stdio.h>

#include "input.h"

#include "map_tile.h"
#include "map_data.h"
#include "chara.h"

#define SPRITE_START_X  8
#define SPRITE_START_Y  16

static uint8_t bgX = 0;
static uint8_t bgY = 0;
static uint8_t spX = SPRITE_START_X;
static uint8_t spY = SPRITE_START_Y;
static int8_t isSprite = 1;

static uint8_t bgNo = 0;

// 8x8のスプライト描画
void SpriteDraw8x8(int8_t idx, int8_t spno, const uint8_t x, const uint8_t y)
{
    for (int8_t i = 0; i < 4; i++) {
        set_sprite_tile(idx, spno);
        move_sprite(idx, x + 8 * (i % 2), y + 8 * (i >> 1));
        ++idx;
        ++spno;
    }
}

// 8x16のスプライト描画
void SpriteDraw8x16(int8_t idx, int8_t spno, const uint8_t x, const uint8_t y)
{
    set_sprite_tile(idx, spno);
    move_sprite(idx, x, y);
    idx++;
    spno += 2;

    set_sprite_tile(idx, spno);
    move_sprite(idx, x + 8, y);
}

// V Blank割込み処理
void VBlankInter(void)
{
    UpdateInput();
    uint8_t keyInput = GetDirect();

    if (keyInput & J_A) {
        keyInput = GetSequence(); 
    } else if (keyInput & J_B) {
        keyInput = GetTrigger();
    }

    if (isSprite) {
        if (keyInput & J_RIGHT) spX++;
        if (keyInput & J_LEFT) spX--;
        if (keyInput & J_DOWN) spY++;
        if (keyInput & J_UP) spY--;
    } else {
        if (keyInput & J_RIGHT) bgX++;
        if (keyInput & J_LEFT) bgX--;
        if (keyInput & J_DOWN) bgY++;
        if (keyInput & J_UP) bgY--;
    }

    if ((GetDirect() & J_START) && (GetDirect() & J_A) && (GetDirect() & J_B)) {
        bgX = bgY = 0;
        spX = SPRITE_START_X;
        spY = SPRITE_START_Y;
    }

    if (GetTrigger() & J_SELECT) {
        isSprite ^= 1;
    }

    // BGタイル表示テスト
    if (!isSprite) {
        set_bkg_tile_xy(2, 4, bgNo);
        if (GetSequence() & J_A) {
            if (bgNo++ > 0x7f) bgNo = 0;
        }
    }

    move_bkg(bgX, bgY);
    SpriteDraw8x16( 0,  0, spX, spY);
}

void main(void)
{
    DISPLAY_OFF;
    HIDE_BKG;

    set_bkg_data(0, 128, MapTile);
    set_bkg_tiles(0, 0, MapDataWidth, MapDataHeight, MapData);

    HIDE_SPRITES;

    SPRITES_8x16;
    set_sprite_data(0, 40, TileData);

    SpriteDraw8x16( 0,  0, SPRITE_START_X     , SPRITE_START_Y);
    SpriteDraw8x16( 2,  4, SPRITE_START_X + 16, SPRITE_START_Y);
    SpriteDraw8x16( 4,  8, SPRITE_START_X + 32, SPRITE_START_Y);
    SpriteDraw8x16( 6, 12, SPRITE_START_X     , SPRITE_START_Y + 16);
    SpriteDraw8x16( 8, 16, SPRITE_START_X + 16, SPRITE_START_Y + 16);
    SpriteDraw8x16(10, 20, SPRITE_START_X + 32, SPRITE_START_Y + 16);
    SpriteDraw8x16(12, 24, SPRITE_START_X     , SPRITE_START_Y + 32);
    SpriteDraw8x16(14, 28, SPRITE_START_X + 16, SPRITE_START_Y + 32);
    SpriteDraw8x16(16, 32, SPRITE_START_X + 32, SPRITE_START_Y + 32);
    SpriteDraw8x16(18, 36, SPRITE_START_X + 48, SPRITE_START_Y + 32);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    // V Blank対応
    disable_interrupts();
    add_VBL(VBlankInter);
    enable_interrupts();
    set_interrupts(VBL_IFLAG);

    while (1) {
        delay(10);
    }
}

