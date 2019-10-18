﻿#include "angband.h"
#include "grid.h"
#include "floor-generate.h"
#include "rooms.h"
#include "rooms-normal.h"
#include "floor.h"
#include "dungeon.h"

/*!
* @brief タイプ9の部屋…フラクタルカーブによる洞窟生成 / Type 9 -- Driver routine to create fractal p_ptr->current_floor_ptr->grid_array system
* @return なし
*/
bool build_type9(floor_type *floor_ptr)
{
	int grd, roug, cutoff;
	POSITION xsize, ysize, y0, x0;

	bool done, light, room;

	/* get size: note 'Evenness'*/
	xsize = randint1(22) * 2 + 6;
	ysize = randint1(15) * 2 + 6;

	/* Find and reserve some space in the dungeon.  Get center of room. */
	if (!find_space(&y0, &x0, ysize + 1, xsize + 1))
	{
		/* Limit to the minimum room size, and retry */
		xsize = 8;
		ysize = 8;

		/* Find and reserve some space in the dungeon.  Get center of room. */
		if (!find_space(&y0, &x0, ysize + 1, xsize + 1))
		{
			/*
			* Still no space?!
			* Try normal room
			*/
			return build_type1(floor_ptr);
		}
	}

	light = done = FALSE;
	room = TRUE;

	if ((floor_ptr->dun_level <= randint1(25)) && !(d_info[p_ptr->dungeon_idx].flags1 & DF1_DARKNESS)) light = TRUE;

	while (!done)
	{
		/* Note: size must be even or there are rounding problems
		* This causes the tunnels not to connect properly to the room */

		/* testing values for these parameters feel free to adjust */
		grd = 1 << (randint0(4));

		/* want average of about 16 */
		roug = randint1(8) * randint1(4);

		/* about size/2 */
		cutoff = randint1(xsize / 4) + randint1(ysize / 4) +
			randint1(xsize / 4) + randint1(ysize / 4);

		/* make it */
		generate_hmap(floor_ptr, y0, x0, xsize, ysize, grd, roug, cutoff);

		/* Convert to normal format + clean up */
		done = generate_fracave(floor_ptr, y0, x0, xsize, ysize, cutoff, light, room);
	}

	return TRUE;
}
