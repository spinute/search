// © 2013 the Search Authors under the MIT license. See AUTHORS for the list of authors.

// Benchmarking for some common basic operations.
//
// Take care when writing these benchmarks that the calls
// to the functions being benchmarked don't actually get
// optimized away.  One way to avoid this is to assign their
// result to some static memory.

#include "utils.hpp"
#include <cmath>
#include <ctime>
#include <cstdlib>

volatile unsigned int ivol;
volatile double dvol;

extern unsigned int *randuints(unsigned long);
extern double *randdoubles(unsigned long);

void new_16_delete_bench(unsigned long n, double *strt, double *end) {
	for (unsigned long i = 0; i < n; i++)
		delete[]  new char[16];
}

void new_32_delete_bench(unsigned long n, double *strt, double *end) {
	for (unsigned long i = 0; i < n; i++)
		delete[]  new char[32];
}

void new_128_delete_bench(unsigned long n, double *strt, double *end) {
	for (unsigned long i = 0; i < n; i++)
		delete[]  new char[128];
}

void walltime_bench(unsigned long n, double *strt, double *end) {
	for (unsigned long i = 0; i < n; i++)
		dvol = walltime();
}

void cputime_bench(unsigned long n, double *strt, double *end) {
	for (unsigned long i = 0; i < n; i++)
		dvol = cputime();
}

void rand_bits_bench(unsigned long n, double *strt, double *end) {
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		ivol = randgen.bits();
}

void rand_real_bench(unsigned long n, double *strt, double *end) {
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = randgen.real();
}

void rand_bench(unsigned long n, double *strt, double *end) {
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		ivol = rand();
}

void ilog2_bench(unsigned long n, double *strt, double *end) {
	unsigned int *is = randuints(n);
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		ivol = ilog2(is[i]);
}

void log2_int_bench(unsigned long n, double *strt, double *end) {
	unsigned int *is = randuints(n);
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		ivol= log2(is[i]);
}

void log2_double_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = log2(is[i]);
}

void sqrt_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n + 1);
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = sqrt(is[i]);
}

void atan2_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);
	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = atan2(is[i], is[i+1]);
}

void sin_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);

	for (unsigned long i = 0; i < n; i++)
		is[i] *= M_PI * 2;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = sin(is[i]);
}

void cos_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);

	for (unsigned long i = 0; i < n; i++)
		is[i] *= M_PI * 2;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = cos(is[i]);
}

void pow_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n + 1);

	for (unsigned long i = 0; i < n + 1; i++)
		is[i] *= randgen.real() * 64;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = pow(is[i], is[i+1]);
}

void pow_ints_bench(unsigned long n, double *strt, double *end) {
	unsigned int *is = randuints(n + 1);

	for (unsigned long i = 0; i < n + 1; i++)
		is[i] &= 0x3F;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		ivol = pow(is[i], is[i+1]);
}

void ipow_bench(unsigned long n, double *strt, double *end) {
	unsigned int *is = randuints(n + 1);

	for (unsigned long i = 0; i < n + 1; i++)
		is[i] &= 0x3F;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		ivol = ipow(is[i], is[i+1]);
}

void ceil_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);

	for (unsigned long i = 0; i < n; i++)
		is[i] *= 1000;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = ceil(is[i]);
}

void floor_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);

	for (unsigned long i = 0; i < n; i++)
		is[i] *= 1000;

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = floor(is[i]);
}

void phi_bench(unsigned long n, double *strt, double *end) {
	double *is = randdoubles(n);

	*strt = walltime();

	for (unsigned long i = 0; i < n; i++)
		dvol = phi(is[i]);
}