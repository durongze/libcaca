/*
 *   ttyvaders     Textmode shoot'em up
 *   Copyright (c) 2002 Sam Hocevar <sam@zoy.org>
 *                 All Rights Reserved
 *
 *   $Id$
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "config.h"

#include <stdlib.h>

#include "common.h"

static void draw_alien_foo(game *, int, int, int);
static void draw_alien_bar(game *, int, int, int);
static void draw_alien_baz(game *, int, int, int);

struct ee_sprite *foo_sprite;
struct ee_sprite *bar_sprite;
struct ee_sprite *baz_sprite;

void init_aliens(game *g, aliens *al)
{
    int i;

    for(i = 0; i < ALIENS; i++)
    {
        al->type[i] = ALIEN_NONE;
    }

    foo_sprite = ee_load_sprite("data/foo_fighter");
    bar_sprite = ee_load_sprite("data/bar_fighter");
    baz_sprite = ee_load_sprite("data/baz_fighter");
}

void draw_aliens(game *g, aliens *al)
{
    int i;

    for(i = 0; i < ALIENS; i++)
    {
        switch(al->type[i])
        {
            case ALIEN_FOO:
                draw_alien_foo(g, al->x[i], al->y[i], al->img[i] % 8);
                break;
            case ALIEN_BAR:
                draw_alien_bar(g, al->x[i], al->y[i], al->img[i] % 2);
                break;
            case ALIEN_BAZ:
                draw_alien_baz(g, al->x[i], al->y[i], al->img[i] % 6);
                break;
            case ALIEN_NONE:
                break;
        }
    }
}

void update_aliens(game *g, aliens *al)
{
    int i;

    for(i = 0; i < ALIENS; i++)
    {
        /* If alien died, make it explode */
        if(al->type[i] != ALIEN_NONE && al->life[i] < 0)
        {
            add_explosion(g, g->ex, al->x[i], al->y[i], 0, 0, EXPLOSION_MEDIUM);
            al->type[i] = ALIEN_NONE;
            add_bonus(g, g->bo, al->x[i], al->y[i], ee_rand(0,4) ? BONUS_GREEN : BONUS_LIFE);
        }

        /* Update coordinates */
        switch(al->type[i])
        {
            case ALIEN_FOO:
            case ALIEN_BAR:
            case ALIEN_BAZ:
                al->x[i] = ((al->x[i] + 5) % (g->w + 3)) - 3;
                al->y[i] = al->y[i] + (rand() % 8) / 7 - (rand() % 8) / 7;
                al->img[i] = al->img[i] + 1;

                /* Check bounds */
                if(al->y[i] < 0 ) al->y[i] = 0;
                if(al->y[i] > g->w - 1 ) al->y[i] = g->w - 1;
                break;
            case ALIEN_NONE:
                break;
        }
    }
}

void add_alien(game *g, aliens *al, int x, int y, int type)
{
    int i;

    for(i = 0; i < ALIENS; i++)
    {
        if(al->type[i] == ALIEN_NONE)
        {
            al->type[i] = type;
            al->x[i] = x;
            al->y[i] = y;
            al->img[i] = 0;

            switch(al->type[i])
            {
                case ALIEN_FOO:
                    al->life[i] = 3;
                    break;
                case ALIEN_BAR:
                    al->life[i] = 3;
                    break;
                case ALIEN_BAZ:
                    al->life[i] = 3;
                    break;
                case ALIEN_NONE:
                    break;
            }

            break;
        }
    }
}

static void draw_alien_bar(game *g, int x, int y, int frame)
{
    ee_set_sprite_frame(bar_sprite, frame);
    ee_draw_sprite(x, y, bar_sprite);
}

static void draw_alien_baz(game *g, int x, int y, int frame)
{
    ee_set_sprite_frame(baz_sprite, frame);
    ee_draw_sprite(x, y, baz_sprite);
}

static void draw_alien_foo(game *g, int x, int y, int frame)
{
    ee_set_sprite_frame(foo_sprite, frame);
    ee_draw_sprite(x, y, foo_sprite);
}


