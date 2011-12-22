#include "body.hpp"
#include "tile.hpp"
#include <cstdio>
#include <vector>

struct Image;

struct Lvl {

	Lvl(unsigned int, unsigned int, unsigned int);

	Lvl(FILE*);

	~Lvl(void);

	unsigned int width(void) const { return w; }

	unsigned int height(void) const { return h; }

	unsigned int depth(void) const { return d; }

	void draw(Image&) const;

	Isect isection(unsigned int, const Bbox&, const Point&) const;

	struct Blk { unsigned int tile; };

	struct Blkinfo {
		Blkinfo(const Blk &b, unsigned int _x, unsigned int _y) :
			blk(b), tile(tiles[b.tile]), x(_x), y(_y) { }

		const Blk &blk;
		const Tile &tile;
		unsigned int x, y;
	};

	bool blocked(unsigned int x, unsigned int y, unsigned int z) const {
		return tiles[blks[ind(x, y, z)].tile].flags & Tile::Collide;
	}

	Blkinfo at(unsigned int x, unsigned int y, unsigned int z) const {
		return Blkinfo(blks[ind(x, y, z)], x, y);
	}

	Blkinfo majorblk(unsigned int z, const Bbox &r) const {
		double x = (r.max.x + r.min.x) / 2.0;
		double y = (r.max.y + r.min.y) / 2.0;
		return at(x / Tile::Width, y / Tile::Height, z);
	}

	// polys returns a vector of polygons that represent the
	// given z-layer of the level.
	std::vector<Polygon> polys(unsigned int) const;

private:

	void read(FILE*);

	void readtile(FILE*, unsigned int, unsigned int, unsigned int);

	unsigned int ind(unsigned int x, unsigned int y, unsigned int z) const {
		return z * w * h + y * w + x;
	}

	Blk *blk(unsigned int x, unsigned int y, unsigned int z) {
		return blks + ind(x, y, z);
	}

	unsigned int w, h, d;

	Blk *blks;
};