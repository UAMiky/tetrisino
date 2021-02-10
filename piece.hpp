#ifndef UAMIKE_TETRISINO_PIECE_HPP
#define UAMIKE_TETRISINO_PIECE_HPP

#include <arduino.h>

namespace uamike {
namespace tetrisino {

struct Piece
{
  byte data[4];
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_PIECE_HPP
