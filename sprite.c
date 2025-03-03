#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

#include "map_tile.c"
#include "map_data.c"
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

    set_bkg_data(0, 4, MapTile);
    set_bkg_tiles(0, 0, 20, 18, MapData);

    HIDE_SPRITES;

    SPRITES_8x16;
    set_sprite_data(0, 12, TileData);

    SpriteDraw8x16(0, 0, SPRITE_START_X     , SPRITE_START_Y);
    SpriteDraw8x16(2, 4, SPRITE_START_X + 16, SPRITE_START_Y);
    SpriteDraw8x16(4, 8, SPRITE_START_X + 32, SPRITE_START_Y);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

