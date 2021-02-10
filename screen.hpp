#ifndef UAMIKE_TETRISINO_SCREEN_HPP
#define UAMIKE_TETRISINO_SCREEN_HPP

#include <arduino.h>

namespace uamike {
namespace tetrisino {

struct Piece;

struct Screen
{
  bool check_piece(const Piece& piece, char x, char y);
  void add_piece(const Piece& piece, char x, char y);

private:
  typedef byte Segment_t[8];
  Segment_t screen[4] {};
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_SCREEN_HPP
