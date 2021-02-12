#ifndef UAMIKE_TETRISINO_SCREEN_HPP
#define UAMIKE_TETRISINO_SCREEN_HPP

#include <arduino.h>

namespace uamike {
namespace tetrisino {

struct Piece;

struct Screen
{
  typedef byte Segment_t[8];
  typedef Segment_t ScreenState[4];

  bool check_piece(const Piece& piece, char x, char y);
  void add_piece(const Piece& piece, char x, char y);
  void remove_piece(const Piece& piece, char x, char y);

private:

  ScreenState screen;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_SCREEN_HPP
