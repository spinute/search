#include <cassert>
#include <boost/cstdint.hpp>
#include <boost/integer/static_log2.hpp>

void fatal(const char*, ...);
extern "C" unsigned long hashbytes(unsigned char[], unsigned int);

class Tiles;

template<int Ntiles> class PackedTiles {
	friend class Tiles;

	enum {
		Nbits = boost::static_log2<Ntiles>::value,
		Nbytes = (int) ((Nbits / 8.0) * Ntiles),
	};

	unsigned char bytes[Nbytes];

public:

	void pack(Tiles::Tile ts[]) {
		fatal("Tiles::pack is unimplemented");
	}

	Tiles::Pos unpack(Tiles::Tile ts[]) {
		fatal("Tiles::unpack is unimplemented");
		return 0;
	}

	Tiles::Pos unpack_md(const unsigned int md[][Ntiles], Tiles::Tile ts[], Tiles::Cost *h) {
		*h = 0;
		fatal("Tiles::unpack_md is unimplemented");
		return 0;
	}

	unsigned long hash(void) {
		return hashbytes(bytes, sizeof(bytes));
	}

	bool operator==(PackedTiles &o) const {
		return memcmp(bytes, o.bytes, sizeof(bytes)) == 0;
	}
};

template<> class PackedTiles<16> {
	friend class Tiles;

	enum { Ntiles = 16 };

	boost::uint64_t word;

public:

	void pack(Tiles::Tile ts[]) {
		word = 0;
		for (int i = 0; i < Ntiles; i++)
			word = (word << 4) | ts[i];
	}

	Tiles::Pos unpack(Tiles::Tile ts[]) {
		int b;
		boost::uint64_t w = word;
		for (int i = Ntiles - 1; i >= 0; i--) {
			Tiles::Tile t = w & 0xF;
			w >>= 4;
			ts[i] = t;
			if (t == 0)
				b = i;
		}
		return b;
	}

	Tiles::Pos unpack_md(const unsigned int md[][Ntiles], Tiles::Tile ts[], Tiles::Cost *hp) {
		int b;
		Tiles::Cost h = 0;
		boost::uint64_t w = word;
		for (int i = Ntiles - 1; i >= 0; i--) {
			Tiles::Tile t = w & 0xF;
			w >>= 4;
			ts[i] = t;
			if (t == 0)
				b = i;
			else
				h += md[t][i];
		}
		*hp = h;
		return b;
	}

	unsigned long hash(void) {
		return word;
	}

	bool operator==(const PackedTiles &o) const {
		return word == o.word;
	}
};
