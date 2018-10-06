/*
 * *****************************************************************************
 *
 * Copyright 2018 Gavin D. Howard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * *****************************************************************************
 *
 * The main procedure of dc.
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <status.h>
#include <vector.h>
#include <dc.h>
#include <vm.h>
#include <args.h>

BcStatus dc_main(int argc, char *argv[]) {

	BcStatus s;
	BcVec files, exprs;
	unsigned int flags = BC_FLAG_Q;

	bcg.sig_msg = dc_sig_msg;
	bcg.bc = false;

	if ((s = bc_vec_init(&files, sizeof(char*), NULL))) return s;
	if ((s = bc_vec_init(&exprs, sizeof(char), NULL))) goto exprs_err;

	if((s = bc_args(argc, argv, dc_help, &flags, &exprs, &files))) goto err;

	s = bc_vm_exec(flags, &exprs, &files, '[', ']',
	               dc_parse_init, dc_parse_expr);

err:
	bc_vec_free(&exprs);
exprs_err:
	bc_vec_free(&files);
	return s;
}
