#ifndef UAMIKE_TETRISINO_SCREEN_HPP
#define UAMIKE_TETRISINO_SCREEN_HPP

#include <arduino.h>

#include "InputState.hpp"

namespace uamike {
namespace tetrisino {

struct Piece;

struct Screen
{
  typedef byte Segment_t[8];
  typedef Segment_t State[4];

  void begin();

  void clear();
  bool check_piece(const Piece& piece, char x, char y);
  void add_piece(const Piece& piece, char x, char y);
  void remove_piece(const Piece& piece, char x, char y);
  bool move_piece(const Piece*& piece, const InputState& input, char& x, char& y);
  unsigned int check_and_remove_lines(char y, int audio_pin);

  void game_over(byte score, int audio_pin);

private:

  State screen;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_SCREEN_HPP
