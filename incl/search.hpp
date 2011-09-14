#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

#include <cstdio>
#include <vector>

double walltime(void);
double cputime(void);
void dfpair(FILE *f, const char *key, const char *fmt, ...);

template <class D> struct Result {
	double wallstrt, cpustrt;
	double wallend, cpuend;
	unsigned long expd, gend, reopnd;
	long dups;
	typename D::Cost cost;
	std::vector<typename D::State> path;

	Result(bool dups = false) :
		expd(0), gend(0), reopnd(0),
		dups(-1), cost(D::InfCost) {
		if (dups)
			dups = 0;
		start();
	}

	void start(void) {
		wallstrt = walltime();
		cpustrt = cputime();
	}

	void finish(void) {
		wallend = walltime();
		cpuend = cputime();
	}

	void output(FILE *f) {
		dfpair(f, "state size", "%u", sizeof(typename D::State));
		dfpair(f, "packed state size", "%u", sizeof(typename D::PackedState));
		dfpair(f, "total raw cpu time", "%g", cpuend - cpustrt);
		dfpair(f, "total wall time", "%g", wallend - wallstrt);
		dfpair(f, "total nodes expanded", "%lu", expd);
		dfpair(f, "total nodes generated", "%lu", gend);
		if (dups >= 0)
			dfpair(f, "total nodes duplicated", "%ld", dups);
		dfpair(f, "total reopened", "%ld", reopnd);
		dfpair(f, "final sol cost", "%g", (double) cost);
		dfpair(f, "final sol length", "%lu", (unsigned long) path.size());
	}
};

template <class D> class Search {
public:
	virtual Result<D> search(D &, typename D::State &) = 0;
};

#endif	// _SEARCH_HPP_
