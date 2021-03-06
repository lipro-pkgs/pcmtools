/*
 * Core functions to handle different PC/M character generator PROMs.
 *
 * Copyright (C) 2002-2020  Stephan Linz <linz@li-pro.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include "pcmtools.h"

bool mkcg_out_xxd(mkcg_cg *cg, mkcg_ch *ch, unsigned int addr)
{
	unsigned int	cnt, cnt_w, cnt_h, bit, bits, bytes;

	OUT("%07X: ", addr);

	bytes = 0;

	for (cnt_h = 0; cnt_h < ch->image.height; cnt_h++) {

		for (cnt_w = bits = 0; cnt_w < ch->image.width; cnt_w++) {

			bit = (ch->image.data[cnt_h * ch->image.width + cnt_w]
					== ch->dot_color_id) ? 1 : 0;
			bits += bit;
			bits <<= 1;

		}

		bytes++;

		bits >>= 1;
		bits = cg->options & OPT_MKCG_NEGATED ? ~bits : bits;
		bits &= (1 << cg->bound_bits) - 1;

		OUT("%02X ", cg->options & OPT_MKCG_LEFTBOUND ? (bits << (8 - cg->bound_bits)) : bits);

	}

	for (cnt = 0; cnt < cg->bound_bytes - bytes; cnt++) {

		bits = cg->options & OPT_MKCG_NEGATED ? ~0 : 0;
		bits &= (1 << cg->bound_bits) - 1;

		OUT("%02X ", cg->options & OPT_MKCG_LEFTBOUND ? (bits << (8 - cg->bound_bits)) : bits);

	}

	OUT("%s", "\n");

	return true;
}
