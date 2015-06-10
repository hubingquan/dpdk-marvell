/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2015 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/queue.h>

#include <rte_cycles.h>
#include <rte_random.h>
#include <rte_hash.h>
#include <rte_jhash.h>
#include <rte_hash_crc.h>

#include "test.h"

/*
 * Hash values calculated for key sizes from array "hashtest_key_lens"
 * and for initial values from array "hashtest_initvals.
 * Each key will be formed by increasing each byte by 1:
 * e.g.: key size = 4, key = 0x03020100
 *       key size = 8, key = 0x0706050403020100
 */
static uint32_t hash_values_jhash[2][10] = {{
	0x821cc2db, 0xa491f494, 0xace4cd87, 0x9e867842,
	0xd32442d6, 0x5fbafeab, 0x9cac434c, 0xecad9b0d,
	0x2dcf235e, 0xaab655d0
},
{
	0xc1111b14, 0x9a95039e, 0x84f208a0, 0xfa28f3fb,
	0xfa13f7d3, 0xc7aed470, 0x74caa938, 0xa9288066,
	0xd0140735, 0xbf00519d
}
};
static uint32_t hash_values_crc[2][10] = {{
	0x91545164, 0x06040eb1, 0x9bb99201, 0xcc4c4fe4,
	0x14a90993, 0xf8a5dd8c, 0xc62beb31, 0x32bf340e,
	0x72f9d22b, 0x4a11475e
},
{
	0x98cd4c70, 0xd52c702f, 0x41fc0e1c, 0x3905f65c,
	0x94bff47f, 0x1bab102d, 0xd2911ed7, 0xe8faa813,
	0x6bea184b, 0x53028d3e
}
};

/*******************************************************************************
 * Hash function performance test configuration section. Each performance test
 * will be performed HASHTEST_ITERATIONS times.
 *
 * The three arrays below control what tests are performed. Every combination
 * from the array entries is tested.
 */
#define HASHTEST_ITERATIONS 1000000

static rte_hash_function hashtest_funcs[] = {rte_jhash, rte_hash_crc};
static uint32_t hashtest_initvals[] = {0, 0xdeadbeef};
static uint32_t hashtest_key_lens[] = {
	4, 8, 16, 32, 48, 64, /* standard key sizes */
	9,                    /* IPv4 SRC + DST + protocol, unpadded */
	13,                   /* IPv4 5-tuple, unpadded */
	37,                   /* IPv6 5-tuple, unpadded */
	40                    /* IPv6 5-tuple, padded to 8-byte boundary */
};
/******************************************************************************/

/*
 * To help print out name of hash functions.
 */
static const char *
get_hash_name(rte_hash_function f)
{
	if (f == rte_jhash)
		return "jhash";

	if (f == rte_hash_crc)
		return "rte_hash_crc";

	return "UnknownHash";
}

/*
 * Test a hash function.
 */
static void
run_hash_func_perf_test(uint32_t key_len, uint32_t init_val,
		rte_hash_function f)
{
	static uint8_t key[HASHTEST_ITERATIONS][RTE_HASH_KEY_LENGTH_MAX];
	uint64_t ticks, start, end;
	unsigned i, j;

	for (i = 0; i < HASHTEST_ITERATIONS; i++) {
		for (j = 0; j < key_len; j++)
			key[i][j] = (uint8_t) rte_rand();
	}

	start = rte_rdtsc();
	for (i = 0; i < HASHTEST_ITERATIONS; i++)
		f(key[i], key_len, init_val);
	end = rte_rdtsc();
	ticks = end - start;

	printf("%-12s, %-18u, %-13u, %.02f\n", get_hash_name(f), (unsigned) key_len,
			(unsigned) init_val, (double)ticks / HASHTEST_ITERATIONS);
}

/*
 * Test all hash functions.
 */
static void
run_hash_func_perf_tests(void)
{
	unsigned i, j, k;

	printf(" *** Hash function performance test results ***\n");
	printf(" Number of iterations for each test = %d\n",
			HASHTEST_ITERATIONS);
	printf("Hash Func.  , Key Length (bytes), Initial value, Ticks/Op.\n");

	for (i = 0; i < RTE_DIM(hashtest_initvals); i++) {
		for (j = 0; j < RTE_DIM(hashtest_key_lens); j++) {
			for (k = 0; k < RTE_DIM(hashtest_funcs); k++) {
				run_hash_func_perf_test(hashtest_key_lens[j],
						hashtest_initvals[i],
						hashtest_funcs[k]);
			}
		}
	}
}

/*
 * Verify that hash functions return what they are expected to return
 * (using precalculated values stored above)
 */
static int
verify_precalculated_hash_func_tests(void)
{
	unsigned i, j;
	uint8_t key[64];
	uint32_t hash;

	for (i = 0; i < 64; i++)
		key[i] = (uint8_t) i;

	for (i = 0; i < sizeof(hashtest_key_lens) / sizeof(uint32_t); i++) {
		for (j = 0; j < sizeof(hashtest_initvals) / sizeof(uint32_t); j++) {
			hash = rte_jhash(key, hashtest_key_lens[i],
					hashtest_initvals[j]);
			if (hash != hash_values_jhash[j][i]) {
				printf("jhash for %u bytes with initial value 0x%x."
				       "Expected 0x%x, but got 0x%x\n",
				       hashtest_key_lens[i], hashtest_initvals[j],
				       hash_values_jhash[j][i], hash);
				return -1;
			}

			hash = rte_hash_crc(key, hashtest_key_lens[i],
					hashtest_initvals[j]);
			if (hash != hash_values_crc[j][i]) {
				printf("CRC for %u bytes with initial value 0x%x."
				       "Expected 0x%x, but got 0x%x\n",
				       hashtest_key_lens[i], hashtest_initvals[j],
				       hash_values_crc[j][i], hash);
				return -1;
			}
		}
	}

	return 0;
}

/*
 * Verify that rte_jhash and rte_jhash2 return the same
 */
static int
verify_jhash_32bits(void)
{
	unsigned i, j;
	uint8_t key[64];
	uint32_t hash, hash32;

	for (i = 0; i < 64; i++)
		key[i] = rand() & 0xff;

	for (i = 0; i < sizeof(hashtest_key_lens) / sizeof(uint32_t); i++) {
		for (j = 0; j < sizeof(hashtest_initvals) / sizeof(uint32_t); j++) {
			/* Key size must be multiple of 4 (32 bits) */
			if ((hashtest_key_lens[i] & 0x3) == 0) {
				hash = rte_jhash(key, hashtest_key_lens[i],
						hashtest_initvals[j]);
				/* Divide key length by 4 in rte_jhash for 32 bits */
				hash32 = rte_jhash2((const uint32_t *)key,
						hashtest_key_lens[i] >> 2,
						hashtest_initvals[j]);
				if (hash != hash32) {
					printf("rte_jhash returns different value (0x%x)"
					       "than rte_jhash2 (0x%x)\n",
					       hash, hash32);
					return -1;
				}
			}
		}
	}

	return 0;
}

/*
 * Run all functional tests for hash functions
 */
static int
run_hash_func_tests(void)
{
	if (verify_precalculated_hash_func_tests() != 0)
		return -1;

	if (verify_jhash_32bits() != 0)
		return -1;

	return 0;

}

static int
test_hash_functions(void)
{
	if (run_hash_func_tests() != 0)
		return -1;

	run_hash_func_perf_tests();

	return 0;
}

static struct test_command hash_functions_cmd = {
	.command = "hash_functions_autotest",
	.callback = test_hash_functions,
};
REGISTER_TEST_COMMAND(hash_functions_cmd);
