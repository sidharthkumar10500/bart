/* Copyright 2013. The Regents of the University of California.
 * All rights reserved. Use of this source code is governed by 
 * a BSD-style license which can be found in the LICENSE file.
 *
 * Authors:
 * 2013 Martin Uecker <uecker@eecs.berkeley.edu>
 */
 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <complex.h>
#include <stdio.h>

#include "num/multind.h"
#include "num/init.h"

#include "misc/mmio.h"
#include "misc/misc.h"
#include "misc/opts.h"

#ifndef DIMS
#define DIMS 16
#endif

static const char help_str[] = "Multiply input1 with scale factor and add input2.\n";


int main_saxpy(int argc, char* argv[argc])
{
	complex float scale = 0;
	const char* in1_file = NULL;
	const char* in2_file = NULL;
	const char* out_file = NULL;

	struct arg_s args[] = {

		ARG_CFL(false, &scale, "scale"),
		ARG_INFILE(false, &in1_file, "input1"),
		ARG_INFILE(false, &in2_file, "input2"),
		ARG_OUTFILE(false, &out_file, "output"),
	};
	const struct opt_s opts[] = {};
	cmdline(&argc, argv, ARRAY_SIZE(args), args, help_str, ARRAY_SIZE(opts), opts);

	num_init();

	const int N = DIMS;
	long dims1[N];
	long dims2[N];

	complex float* data1 = load_cfl(in1_file, N, dims1);
	complex float* data2 = load_cfl(in2_file, N, dims2);

	for (int i = 0; i < N; i++)
		assert(dims1[i] == dims2[i]);

	complex float* out = create_cfl(out_file, N, dims2);

	#pragma omp parallel for
	for (long i = 0; i < md_calc_size(N, dims1); i++)
		out[i] = scale * data1[i] + data2[i];

	unmap_cfl(N, dims1, data1);
	unmap_cfl(N, dims2, data2);
	unmap_cfl(N, dims2, out);
	return 0;
}


