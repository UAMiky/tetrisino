#include "piece.hpp"

namespace uamike {
namespace tetrisino {

const Piece piece_O    {0,  {0b0000, 0b0110, 0b0110, 0b0000}};

const Piece piece_I0   {2,  {0b0010, 0b0010, 0b0010, 0b0010}};
const Piece piece_I90  {1,  {0b0000, 0b0000, 0b1111, 0b0000}};

const Piece piece_L0   {4,  {0b0000, 0b1110, 0b0010, 0b0000}};
const Piece piece_L90  {5,  {0b0010, 0b0010, 0b0110, 0b0000}};
const Piece piece_L180 {6,  {0b0000, 0b1000, 0b1110, 0b0000}};
const Piece piece_L270 {3,  {0b0110, 0b0100, 0b0100, 0b0000}};

const Piece piece_J0   {8,  {0b0010, 0b1110, 0b0000, 0b0000}};
const Piece piece_J90  {9,  {0b0100, 0b0100, 0b0110, 0b0000}};
const Piece piece_J180 {10, {0b1110, 0b1000, 0b0000, 0b0000}};
const Piece piece_J270 {7,  {0b0110, 0b0010, 0b0010, 0b0000}};

const Piece piece_T0   {12, {0b0100, 0b0110, 0b0100, 0b0000}};
const Piece piece_T90  {13, {0b1110, 0b0100, 0b0000, 0b0000}};
const Piece piece_T180 {14, {0b0010, 0b0110, 0b0010, 0b0000}};
const Piece piece_T270 {11, {0b0000, 0b0100, 0b1110, 0b0000}};

const Piece piece_S0   {16, {0b0010, 0b0110, 0b0100, 0b0000}};
const Piece piece_S90  {15, {0b0000, 0b1100, 0b0110, 0b0000}};

const Piece piece_Z0   {18, {0b0100, 0b0110, 0b0010, 0b0000}};
const Piece piece_Z90  {17, {0b0000, 0b0110, 0b1100, 0b0000}};

//const Piece piece
static const Piece* c_pieces[] =
{
  &piece_O,
  &piece_I0, &piece_I90,
  &piece_L0, &piece_L90, &piece_L180, &piece_L270,
  &piece_J0, &piece_J90, &piece_J180, &piece_J270,
  &piece_T0, &piece_T90, &piece_T180, &piece_T270,
  &piece_S0, &piece_S90,
  &piece_Z0, &piece_Z90
};

static const Piece* Piece::get_piece(byte idx)
{
  return (idx < 19) ? c_pieces[idx] : nullptr;
}

static const byte c_pieces_idx[] = {0, 1, 3, 7, 11, 15, 17};
const Piece* Piece::random_piece()
{
  long idx = random(0, 7);
  const Piece* ret_val = c_pieces[c_pieces_idx[idx]];
  idx = random(0, 4);
  for (long i = 0; i < idx; ++i)
  {
    ret_val = rotate(ret_val);
  }
  return ret_val;
}

const Piece* Piece::rotate(const Piece* piece)
{
  return c_pieces[piece->next];
}

}  // namespace tetrisino
}  // namespace uamike
