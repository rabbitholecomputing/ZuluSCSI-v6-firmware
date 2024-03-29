//	Copyright (C) 2020 Michael McMaster <michael@codesrc.com>
//
//	This file is part of SCSI2SD.
//
//	SCSI2SD is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	SCSI2SD is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with SCSI2SD.  If not, see <http://www.gnu.org/licenses/>.
#include "crc.h"

// Use standard CRC-32 reversed poly
#define POLYNOMIAL 0xEDB88320

// Slow (but small) implementation that doesn't use lookup tables.
uint32_t s2s_crc32(uint8_t* data, int len)
{
	uint32_t crc = 0xFFFFFFFF;
	for (int i = 0; i < len; ++i)
	{
		uint32_t byte = data[i];
		crc = crc ^ byte;
		for (int j = 7; j >= 0; j--)
		{
			uint32_t mask = -(crc & 1);
			crc = (crc >> 1) ^ (POLYNOMIAL & mask);
		}
	}
	return ~crc;
}
