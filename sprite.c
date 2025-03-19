#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

#include "map_tile.h"
#include "map_data.h"
#include "chara.h"

#define SPRITE_START_X  8
#define SPRITE_START_Y  16

void SpriteDraw8x8(int8_t idx, int8_t spno, const uint8_t x, const uint8_t y)
{
    for (int8_t i = 0; i < 4; i++) {
        set_sprite_tile(idx, spno);
        move_sprite(idx, x + 8 * (i % 2), y + 8 * (i >> 1));
        ++idx;
        ++spno;
    }
}

void SpriteDraw8x16(int8_t idx, int8_t spno, const uint8_t x, const uint8_t y)
{
    set_sprite_tile(idx, spno);
    move_sprite(idx, x, y);
    idx++;
    spno += 2;

    set_sprite_tile(idx, spno);
    move_sprite(idx, x + 8, y);
}

void main(void)
{
    DISPLAY_OFF;
    HIDE_BKG;

    set_bkg_data(0, 56, MapTile);
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

    uint8_t bgX = 0;
    uint8_t bgY = 0;

    while (1) {
        move_bkg(bgX, bgY);
        bgX++;

        delay(10);
    }
}

