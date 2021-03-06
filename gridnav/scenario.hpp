// Copyright © 2013 the Search Authors under the MIT license. See AUTHORS for the list of authors.
#include "gridmap.hpp"
#include "gridnav.hpp"
#include "../search/search.hpp"
#include <string>
#include <iostream>
#include <cstdio>

struct ScenarioEntry;

std::istream &operator>>(std::istream&, ScenarioEntry&);

struct Scenario;

struct ScenarioEntry {
	ScenarioEntry(Scenario &);
	Result<GridNav> run(unsigned int, SearchAlgorithm<GridNav>*);
private:
	friend std::istream &operator>>(std::istream &, ScenarioEntry &);

	Scenario &scen;
	unsigned int bucket;
	std::string mapfile;
	unsigned int w, h;
	unsigned int x0, y0;
	unsigned int x1, y1;
	double opt;
};

struct Scenario {

	Scenario(int, const char *[]);
	~Scenario();

	void run(std::istream&);
	GridMap *getmap(std::string);

private:
	void checkver(std::istream&);
	void outputhdr(FILE*);

	int argc;
	const char **argv;
	std::string maproot;
	GridMap *lastmap;
	Result<GridNav> res;
	int entry, nentries;
};