#ifndef __COORDINATE_HPP__
#define __COORDINATE_HPP__

// (c) 2010 Geoff Huston
// Licensed under the GPL
//
// This idea actually came from a post somewhere,
// But I totally seem to have lost the link; I'll try
// to find it, or if this seems familiar to anyone,
// let me know.

template< typename t_coord >
class Coordinate {
  public:
    Coordinate() { _coord = 0; };
    Coordinate( t_coord c ) { _coord = c; };

    t_coord operator()() { return _coord; };

    void operator()( t_coord newCoord ) { _coord = newCoord; };

  private:
    t_coord _coord;
};

#endif
