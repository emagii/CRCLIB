/*
 * File:    digest_tab.c
 * Author:  Ulf Samuelsson <ulf@emagii.com>
 *
 * This file is licensed under the MIT License as stated below
 *
 * Copyright (c) 2024 Ulf Samuelsson (ulf@emagii.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "crc.h"

/* Algorithms verified using the string "123456789" on
   http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 */

const algorithm_desc_t algorithms[MAXALGO+1] =
{
  [CRC64_ECMA] =
	{
		crc_algo_64, 64, "CRC64-ECMA",
		.poly.d64 = CRC_POLY_64_ECMA,
		.initial.d64 = CRC_START_64,
		.xor_val.d64 = CRC_END_64,
		.ireflect = false,
		.oreflect = false,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0x6c40df5f0b497347
	},
  [CRC64_WE] =
	{
		crc_algo_64, 64, "CRC64-WE",
		.poly.d64 = CRC_POLY_64_WE,
		.initial.d64 = CRC_START_64_INV,
		.xor_val.d64 = CRC_END_64_INV,
		.ireflect = false,
		.oreflect = false,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0x62ec59e3f1a4f00a
	},
  [CRC64_XZ] =
	{
		crc_algo_64, 64, "CRC64-XZ",
		.poly.d64 = CRC_POLY_64_XZ,
		.initial.d64 = CRC_START_64_INV,
		.xor_val.d64 = CRC_END_64_INV,
		.ireflect = true,
		.oreflect = true,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0x995dc9bbdf1939fa
	},
  [CRC64_ISO] =
	{
		crc_algo_64, 64, "CRC64-GO-ISO",
		.poly.d64 = CRC_POLY_64_ISO,
		.initial.d64 = CRC_START_64_INV,
		.xor_val.d64 = CRC_END_64_INV,
		.ireflect = true,
		.oreflect = true,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0xb90956c775a41001
	},
  [CRC64_ISO_R] =
	{
		crc_algo_64, 64, "CRC64-GO-ISO-R",
		.poly.d64 = CRC_POLY_64_ISO,
		.initial.d64 = CRC_START_64_INV,
		.xor_val.d64 = CRC_END_64_INV,
		.ireflect = false,
		.oreflect = false,
		.reciprocal = true,
		.crc_tab = NULL,
		.expected.d64 = 0xb90956c775a41001
	},
  [CRC32] =
	{
		crc_algo_32, 32, "CRC32",
		.poly.d32._0 = CRC_POLY_32,
		.initial.d64 = CRC_START_32_INV,
		.xor_val.d32._0 = CRC_END_32_INV,
		.ireflect = true,
		.oreflect = true,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0xCBF43926
	},
  [MAXALGO] =
	{
		no_algo, 0, "",
		.poly.d64 = 0,
		.initial.d64 = 0,
		.xor_val.d64 = 0,
		.ireflect = false,
		.oreflect = false,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0
	}
};

algorithm_desc_t algorithm =
{
		no_algo, 0, "",
		.poly.d64 = 0,
		.initial.d64 = 0,
		.xor_val.d64 = 0,
		.ireflect = false,
		.oreflect = false,
		.reciprocal = false,
		.crc_tab = NULL,
		.expected.d64 = 0
};
