#ifndef UAMIKE_TETRISINO_PIECE_HPP
#define UAMIKE_TETRISINO_PIECE_HPP

#include <arduino.h>

namespace uamike {
namespace tetrisino {

struct Piece
{
  byte next;
  byte data[4];

  static const Piece* get_piece(byte idx);
  static const Piece* random_piece();
  static const Piece* rotate(const Piece* piece);
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_PIECE_HPP
