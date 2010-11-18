#ifndef __COORDINATE_HPP__
#define __COORDINATE_HPP__

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
