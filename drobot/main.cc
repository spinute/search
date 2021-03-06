// © 2013 the Search Authors under the MIT license. See AUTHORS for the list of authors.

#include "drobot.hpp"
#include "../search/main.hpp"
#include <cstdio>

int main(int argc, const char *argv[]) {
	dfheader(stdout);
	DockRobot d(stdin);
	search<DockRobot>(d, argc, argv);
	dffooter(stdout);
	return 0;
}