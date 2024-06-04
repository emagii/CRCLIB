/*
 * File:    reflect.c
 * Author:  Ulf Samuelsson <ulf@emagii.com>
 *
 * This file is licensed under the MIT License as stated below
 *
 * Copyright (c) 2023 Ulf Samuelsson (ulf@emagii.com)
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

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>		/* size_t */
#include "crc.h"

extern const algorithm_desc_t algorithms[MAXALGO+1];

algorithm_desc_t	algo;

bool init_algorithm(algorithm_desc_t *a, poly_t poly)
{
	const algorithm_desc_t *p = &algorithms[poly];
	a->crc_algo = p->crc_algo;
	a->crc_size = p->crc_size;
	a->name     = strdup(p->name);
	a->poly.d64 = p->poly.d64;
	a->initial.d64 = p->initial.d64;
	a->xor_val.d64 = p->xor_val.d64;
	a->ireflect    = p->ireflect;
	a->oreflect    = p->oreflect;
	a->reciprocal  = p->reciprocal;
	a->expected.d64 = p->expected.d64;
	a->big_endian   = p->big_endian;
	if (p->crc_size == 32) {
		a->crc_tab      = init_crc32_tab (p);
	} else if (p->crc_size == 64) {
		a->crc_tab      = init_crc64_tab (p);
	} else {
		return false;
	}
	return true;
}

void test()
{

}

void main(void)
{
	/* Memory leak of name and crc_tab */
	if (init_algorithm(&algo, CRC32)) {
		uint32_t crc = calc_crc32 (&algo, "123456789", 9);
		printf("%-16s: ", algo.name);
		printf("CRC = 0x%08X, expected 0x%08X ", crc, algo.expected.d32._0);
		if (crc == algo.expected.d32._0) { printf("OK\n"); } else { printf("FAIL\n"); }
	}
	printf("\n");
	if (init_algorithm(&algo, CRC64_ECMA)) {
		uint64_t crc = calc_crc64 (&algo, "123456789", 9);
		printf("%-16s: ", algo.name);
		printf("CRC = 0x%016lx, expected 0x%016lx ", crc, algo.expected.d64);
		if (crc == algo.expected.d64) { printf("OK\n"); } else { printf("FAIL\n"); }
	}
	if (init_algorithm(&algo, CRC64_WE)) {
		uint64_t crc = calc_crc64 (&algo, "123456789", 9);
		printf("%-16s: ", algo.name);
		printf("CRC = 0x%016lx, expected 0x%016lx ", crc, algo.expected.d64);
		if (crc == algo.expected.d64) { printf("OK\n"); } else { printf("FAIL\n"); }
	}
	if (init_algorithm(&algo, CRC64_XZ)) {
		uint64_t crc = calc_crc64 (&algo, "123456789", 9);
		printf("%-16s: ", algo.name);
		printf("CRC = 0x%016lx, expected 0x%016lx ", crc, algo.expected.d64);
		if (crc == algo.expected.d64) { printf("OK\n"); } else { printf("FAIL\n"); }
	}
	if (init_algorithm(&algo, CRC64_ISO)) {
		uint64_t crc = calc_crc64 (&algo, "123456789", 9);
		printf("%-16s: ", algo.name);
		printf("CRC = 0x%016lx, expected 0x%016lx ", crc, algo.expected.d64);
		if (crc == algo.expected.d64) { printf("OK\n"); } else { printf("FAIL\n"); }
	}
	if (init_algorithm(&algo, CRC64_ISO_R)) {
		uint64_t crc = calc_crc64 (&algo, "123456789", 9);
		printf("%-16s: ", algo.name);
		printf("CRC = 0x%016lx, expected 0x%016lx ", crc, algo.expected.d64);
		if (crc == algo.expected.d64) { printf("OK\n"); } else { printf("FAIL\n"); }
	}
}
